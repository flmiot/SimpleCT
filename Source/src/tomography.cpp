/// ---------------------------------------------------------------------------
// This file is part of SimpleCT. The SimpleCT software is in the public domain,
// furnished "as is", without technical support, and with no warranty, express or
// implied, as to its usefulness for any purpose.
//
// tomography.cpp
// Tomography class implementation.
//
// Author: Florian Otte
// ---------------------------------------------------------------------------
#include "tomography.h"

#include <stdexcept>

#include "wx_frames.h"

using namespace cimg_library;

//
// ============	Helper functions ============
//

void DrawRedLineEmptyImage(wxImage &Image) {
// Purpose: Draws a diagonal red line over black ground
// 			Displayed instead of empty images

	int height = Image.GetHeight();
	int width = Image.GetWidth();
	Image.Destroy();
	Image.Create(width, height);

	for (int i = 0; i < height; i++) {
		Image.SetRGB(i, i, 255, 0, 0);
	};
}

void DrawGreenTriangleBusyImage(wxImage &Image) {
// Purpose: Draws a green triangle in the bottom right corner
// 			Displayed during computation

	int height = Image.GetHeight();
	int width = Image.GetWidth();

	int ypos = 0.8*height;
	while(ypos < height){
		for(int negxpos = 1; negxpos < ypos - 0.8*height; negxpos++){
			Image.SetRGB(width - negxpos, ypos, 0, 255, 0);
		}
		ypos++;
	}
}

//
// ============	Tomography class implementation ============
//

// Purpose: Constructor
// Return:	NA
// Error:	Exception safe / no exceptions
Tomography::Tomography( int size, int angles) :
		_Sinogram(), _Sinogram_ramp(),_Slice_fbp(), _Slice_bp(),
		_ImageBuffer(), _size(size), _angles(angles), _currentComputation(none),
		_progress_computation(0), _CurrentFilter(None), _rotation_center( 0.5 ),
		_i0( 1 ), _correct_dead_pixels( false ), CustomThreadClass() {
}

// Purpose: Destructor
// Return: 	NA
// Error:	Exception safe / no exceptions
Tomography::~Tomography() {
	//global::pConsoleWindow->log(wxT( "Tomographie-Objekt gelöscht." ));
	if(this->_pWorkerThread != NULL) StopTask();
}

// Purpose: Set TomoData image state in a thread-safe fashion
//			Blocks, if another thread is currently setting images states
// Return:	void
// Error:	Exception safe / no exceptions
void Tomography::setImageState(int ImageType, int ImageState) {
	switch (ImageType) {
	case Type_Sinogram:
		_Sinogram.set_state( (enumImageState)ImageState );
		break;
	case Type_Sinogram_ramp:
		_Sinogram_ramp.set_state( (enumImageState)ImageState );
		break;
	case Type_Slice_fbp:
		_Slice_fbp.set_state( (enumImageState)ImageState );
		break;
	case Type_Slice_bp:
		_Slice_bp.set_state( (enumImageState)ImageState );
		break;
	}
}

// Purpose:
// Return:
// Error:
void Tomography::write_to_image_buffer(wxImage& Source) {
	CImg<double> Temp(Source.GetWidth(), Source.GetHeight());
	this->copy_wxImage_to_CImg(Source, Temp);
	_ImageBuffer.paste(Temp);
}

// Purpose:
// Return:
// Error:
void Tomography::load_sinogram_from_image_buffer() {
	CImg<double> Temp = _ImageBuffer.copy();
	_Sinogram.paste( Temp );
	setImageState( Tomography::Type_Sinogram, Tomography::Updated);
}

void Tomography::load_sinogram_from_ascii_file( const char* filepath ){
	cimg_library::CImg<double> input_image;

	try{
		input_image.load_dlm(filepath);
	}
	catch( cimg_library::CImgException &err){
		throw std::runtime_error(err.what());
	}

	this->reset_tomography( input_image.height(), input_image.width() );
	this->_Sinogram.paste(input_image);
	setImageState( Tomography::Type_Sinogram, Tomography::Updated);
}

// Purpose:
// Return:
// Error:
void Tomography::compute_fwp_from_image_buffer() {
	this->set_current_computation(Tomography::fwp);
	this->StartTask();
}

// Purpose:
// Return:
// Error:
void Tomography::compute_fbp( int FilterType) {

	// Only start if sinogram exists (i.e. state is not NA)
	if( _Sinogram.get_state() == Tomography::NA ) return;
	this->_CurrentFilter = (enumFiltering) FilterType;
	this->set_current_computation(Tomography::fbp);
	this->StartTask();
}

// Purpose:
// Return:
// Error:
void Tomography::compute_bp() {

	// Only start if sinogram exists (i.e. state is not NA)
	if( _Sinogram.get_state() == Tomography::NA ) return;
	this->_CurrentFilter = Tomography::None;
	this->set_current_computation(Tomography::bp);
	this->StartTask();
}

// Purpose:
// Return:
// Error:
void Tomography::abort_any_computation() {
	this->StopTask();
}

// Purpose:
// Return:
// Error:
void Tomography::register_new_reading(Reading& NewDataElement) {
	// Purpose: Add a new pixel-value to the sinogram
	// Pixel-Range: 0 to _size -1
	// Angle-Range: 0 to _angels -1

	int Pixel = NewDataElement.Detectorpixel;
	int Angle = NewDataElement.Angle;
	if(Pixel >= _size) return; // TODO exceptions!
	if(Angle >= _angles) return;
	if(!NewDataElement.Valid) return;

	double Value;
	// Do not accept count values smaller 1 (to limit log)
	if(NewDataElement.Value < 1 )
		Value = 1;
	else
		Value = NewDataElement.Value;

	_Sinogram.register_new_value(Pixel, Angle, Value);
	this->setImageState(Type_Sinogram, Updated);
}

// Purpose:
// Return:
// Error:
void Tomography::export_any_as_wxImage(int ImageType, wxImage &Target,
		int MinPixelValue, int MaxPixelValue ) {

	CImg<double> Temp;

	// return prematurely if image state is not Tomography::Updated
	switch(this->get_any_image_state( ImageType )){
	case Tomography::NA :
		DrawRedLineEmptyImage(Target);
		return;
	case Tomography::NoChanges:
		// No Updates have been made, do nothing
		// TODO not yet implemented
		return;
	case Tomography::Is_Currently_In_Use:
		// return green computation indicator triangle
		DrawGreenTriangleBusyImage(Target);
		return;
	}

	switch (ImageType){
	case Type_Sinogram:
		Temp = CImg<double>(_Sinogram.copy());
		if( this->get_dead_pixel_correction() )
			Temp = interpolate_dead_pixels( Temp );
		Temp = correct_image(Temp);
		break;
	case Type_Sinogram_ramp:
		Temp = CImg<double>(_Sinogram_ramp.copy());
		break;
	case Type_Slice_fbp:
		Temp = CImg<double>(_Slice_fbp.copy());
		break;
	case Type_Slice_bp:
		Temp = CImg<double>(_Slice_bp.copy());
		break;
	default:
		return;
	}

	copy_CImg_to_wxImage(Temp, Target, MinPixelValue, MaxPixelValue );
}

// Purpose:
// Return:
// Error:
bool Tomography::is_any_computed(int Type) {
	switch (Type) {
	case Type_Sinogram:
		return _Sinogram.is_computed();
	case Type_Slice_fbp:
		return _Slice_fbp.is_computed();
	case Type_Slice_bp:
		return _Slice_bp.is_computed();
	case Type_Slice_iart:
		return _Slice_iart.is_computed();
	default:
		return false;
	}
}

// Purpose:
// Return:
// Error: No Exceptions
int Tomography::get_any_image_state(int ImageType) {
	switch (ImageType) {
	case Type_Sinogram:
		return _Sinogram.get_state();
		break;
	case Type_Sinogram_ramp:
		return _Sinogram_ramp.get_state();
		break;
	case Type_Slice_fbp:
		return _Slice_fbp.get_state();
		break;
	case Type_Slice_bp:
		return _Slice_bp.get_state();
		break;
	default: return NA;
	}
}

// Purpose:
// Return:
// Error:
int Tomography::get_tomography_size(){
	return _size;
}

// Purpose:
// Return:
// Error:
int Tomography::get_tomography_angles(){
	return _angles;
}

// Purpose:
// Return:
// Error:
int Tomography::get_current_computation() {
	wxCriticalSectionLocker enter(_currentComputationCS);
	return _currentComputation;
}

// Purpose:
// Return:
// Error:
double Tomography::get_current_computation_progress() {
	wxCriticalSectionLocker enter(_progress_computationCS);
	return _progress_computation;
}

bool Tomography::get_dead_pixel_correction(){
	wxCriticalSectionLocker enter( _correct_dead_pixelsCS );
	return _correct_dead_pixels;
}

// Purpose:
// Return:
// Error:
wxThread::ExitCode Tomography::Task() {
	switch(this->get_current_computation()){
	case Tomography::fwp :
		return threadfunc_compute_fwp();
		break;
	case Tomography::fbp :
		return threadfunc_compute_fbp();
		break;
	case Tomography::bp  :
		return threadfunc_compute_bp();
		break;
	case Tomography::iart:
		return threadfunc_compute_iart();
		break;
	default :
		break;
	}
	return (wxThread::ExitCode) 1;
}

// Purpose:
// Return:
// Error:
void Tomography::OnThread_DestructorCall() {
	// Set the current computation state back to none,

}

// Purpose:
// Return:
// Error:
wxThread::ExitCode Tomography::threadfunc_compute_fwp() {
	int iError = EXIT_SUCCESS;

	cimg_library::CImg<double> Image(_ImageBuffer.copy().resize(_size, _size));
	cimg_library::CImg<double> Temp(_angles, _size, 1, 1, 0);
	// TODO check if square and overall dimension

	_Sinogram.set_state(Tomography::Is_Currently_In_Use);

	for (int angleNr = 0; angleNr < _angles; angleNr++) {

		if (this->_pWorkerThread->TestDestroy()) {
			iError = 1;
			break;
		}

		float AngleStepSize = 360.0f / _angles;
		cimg_library::CImg<double> TempRot(
				Image.get_rotate(AngleStepSize * angleNr, _size / 2.0f, _size / 2.0f, 2));

		cimg_forXY(Image,x,y)
		{
			Temp(angleNr, y) += TempRot(x, y);
		}

		// Post computation progress
		set_computation_progress(100.0f / _angles * angleNr);
		wxCommandEvent event(wxEVT_COMMAND_TEXT_UPDATED, COMPUTATION_UPDATED_ID);
		pMainWindow->GetEventHandler()->AddPendingEvent(event);

	}
	if (!iError) {
		_Sinogram.paste(Temp);
		_Sinogram.is_computed(true);
		setImageState(Tomography::Type_Sinogram, Tomography::Updated);
	}
	set_computation_progress( 0.0 );
	this->set_current_computation(Tomography::none);

	if (iError == EXIT_SUCCESS) {
		wxCommandEvent event(wxEVT_COMMAND_TEXT_UPDATED,
				COMPUTATION_SUCCESSFULL_ID);
		pMainWindow->GetEventHandler()->AddPendingEvent(event);
		return (wxThread::ExitCode) iError;
	} else {
		wxCommandEvent event(wxEVT_COMMAND_TEXT_UPDATED,
				COMPUTATION_ERROR_ID);
		pMainWindow->GetEventHandler()->AddPendingEvent(event);
		return (wxThread::ExitCode) iError;

	}
}

// Purpose:
// Return:
// Error:
wxThread::ExitCode Tomography::threadfunc_compute_fbp() {
	int iError = EXIT_SUCCESS;

	cimg_library::CImg<double> Temp_Columnn(_size, 1, 1, 1, 0);
	cimg_library::CImg<double> Temp_Sinogram;
	cimg_library::CImg<double> Temp_Slice;

	switch (_CurrentFilter) {
	case Tomography::None:
		Temp_Sinogram = _Sinogram.copy();
		if( this->get_dead_pixel_correction() )
			Temp_Sinogram = interpolate_dead_pixels( Temp_Sinogram );
		Temp_Sinogram = correct_image( Temp_Sinogram );
		Temp_Slice = _Slice_bp.copy();
		Temp_Slice = 0.0;
		_Slice_bp.set_state(Tomography::Is_Currently_In_Use);
		break;
	case Tomography::Ramp:
		threadfunc_filter_sinogram();
		Temp_Sinogram = _Sinogram_ramp.copy();
		Temp_Slice =  _Slice_fbp.copy();
		Temp_Slice = 0.0;
		_Slice_fbp.set_state(Tomography::Is_Currently_In_Use);
		break;
	default:
		return (wxThread::ExitCode) 1; // TODO implement exceptions
		break;
	}

	// create round mask
	cimg_library::CImg<double> mask(_size, _size, 1, 1, 0);
	double Color = 1.0;
	mask.draw_circle(_size / 2, _size / 2, _size / 2, &Color);

	for (int angleNr = 0; angleNr < _angles; angleNr++) {

		if (this->_pWorkerThread->TestDestroy()) {
			iError = 1;
			break;
		}

		Temp_Columnn = Temp_Sinogram.get_column(angleNr);
		// Shift pixel column according to _rotation_axis
		// TODO criticalSectionLock

		double pixel_shift = Temp_Columnn._height * _rotation_center - Temp_Columnn._height * 0.5;

		if (pixel_shift != 0) Temp_Columnn.shift(0, pixel_shift );

		float AngleStepSize = 180.0f / _angles;
		Temp_Columnn.resize(_size, _size);
		Temp_Columnn.rotate(-AngleStepSize * angleNr, _size / 2.0f, _size / 2.0f, 2);


		Temp_Slice += Temp_Columnn;

		// Post progress
		set_computation_progress( 100.0f /_angles * angleNr );
		wxCommandEvent event(wxEVT_COMMAND_TEXT_UPDATED, COMPUTATION_UPDATED_ID);
		pMainWindow->GetEventHandler()->AddPendingEvent(event);
	}


	if (!iError) {

		// TODO in export_any_... verlagert, um Windowing zu ermöglichen
		//double MaxValue;
		//Temp_Slice.min_max( MaxValue );
		//Temp_Slice.cut(0, MaxValue );
		//Temp_Slice.mul( mask );

		switch (_CurrentFilter) {
		case Tomography::None:
			_Slice_bp.paste(Temp_Slice);
			_Slice_bp.is_computed( true );
			setImageState(Tomography::Type_Slice_bp, Tomography::Updated);
			break;
		case Tomography::Ramp:
			_Slice_fbp.paste(Temp_Slice);
			_Slice_fbp.is_computed( true );
			setImageState(Tomography::Type_Slice_fbp, Tomography::Updated);
			setImageState(Tomography::Type_Sinogram_ramp, Tomography::Updated);
			break;
		}
	}
	else {
		switch (_CurrentFilter) {
		case Tomography::None:
			setImageState(Tomography::Type_Slice_bp, Tomography::Updated);
			break;
		case Tomography::Ramp:
			setImageState(Tomography::Type_Slice_fbp, Tomography::Updated);
			setImageState(Tomography::Type_Sinogram_ramp, Tomography::Updated);
			break;
		}
	}
	set_computation_progress( 0.0 );
	this->set_current_computation(Tomography::none);


	if (iError == EXIT_SUCCESS) {
		wxCommandEvent event(wxEVT_COMMAND_TEXT_UPDATED, COMPUTATION_SUCCESSFULL_ID);
		pMainWindow->GetEventHandler()->AddPendingEvent(event);
		return (wxThread::ExitCode) iError;
	} else {
		wxCommandEvent event(wxEVT_COMMAND_TEXT_UPDATED, COMPUTATION_ERROR_ID);
		pMainWindow->GetEventHandler()->AddPendingEvent(event);
		return (wxThread::ExitCode) iError;
	}
}

// Purpose:
// Return:
// Error:
wxThread::ExitCode Tomography::threadfunc_compute_bp() {
	return threadfunc_compute_fbp();
}

// Purpose:
// Return:
// Error:
wxThread::ExitCode Tomography::threadfunc_compute_iart() {
	return (wxThread::ExitCode) 1; // TODO
}

// Purpose:
// Return:
// Error:
void Tomography::threadfunc_filter_sinogram() {

	CImg<double> fft_in = _Sinogram.copy();
	if( this->get_dead_pixel_correction() )
		fft_in = interpolate_dead_pixels( fft_in );
	fft_in = correct_image( fft_in );
	CImgList<double> fft = fft_in.get_FFT('y', false);

	// TODO implement more filters

	// create ramp filter // TODO check ramp filter
	cimg_library::CImg<double> ramp(fft[0].width(), fft[0].height());

	cimg_forXY(ramp,x,y){
		ramp(x,y) = 1 - cimg::abs(  2.0f * y -  fft[0].height() ) / (1.0f * fft[0].height());
	}
	/*
	for(int y = 0; y < ramp.height(); y++){
		cimg_forX(ramp,x){
			ramp(x,y) =  1 * y / (1.0f * fft[0].height());
		}
	}
*/
	fft[0].mul(ramp);
	fft[1].mul(ramp);

	CImg<double>::FFT(fft[0], fft[1], 'y',  true);
	this->_Sinogram_ramp.paste( fft[0] );
	this->setImageState(Type_Sinogram_ramp, Updated);
}

// Purpose:
// Return:
// Error:
void Tomography::set_computation_progress(double Progress) {
	wxCriticalSectionLocker enter(_progress_computationCS);
	_progress_computation = Progress;
}

// Purpose:
// Return:
// Error:
void Tomography::set_current_computation(enumComputation Computation) {
	wxCriticalSectionLocker enter(this->_currentComputationCS);
	this->_currentComputation = Computation;
}

// Purpose:
// Return:
// Error:
void Tomography::copy_CImg_to_wxImage(cimg_library::CImg<double> &Source, wxImage &Target,
		int MinPixelValue, int MaxPixelValue ){

	// Grey-scale computation only
	if (Source.spectrum() != 1) // grey-scale computation only
		throw std::runtime_error("Berechnungsfehler: Es können nur Graustufen-Bilder "
				"verrechnet werden.");

	// 2D computation only
	if (Source.depth() != 1)
		throw std::runtime_error("Berechnungsfehler: Es können nur 2D-Bilder "
				"verrechnet werden.");

	int
	s_size_x = Source.width(),
	s_size_y = Source.height(),
	t_size_x = Target.GetWidth(),
	t_size_y = Target.GetHeight();

	// Dead pixel correction
	cimg_library::CImg<double> TempSource( Source );

	// Windowing
	double MaxValue;
	TempSource.min_max( MaxValue );
	double MinValue;
	TempSource.max_min( MinValue );
	double Range = MaxValue - MinValue;

	cimg_library::CImg<unsigned char> Temp_Source_char = TempSource.get_cut(MinValue + MinPixelValue /
			100.0 * Range, MinValue + MaxPixelValue / 100.0 * Range ).get_normalize(0, 255);

	wxImage TempTarget(s_size_x, s_size_y, true);

	unsigned char
	*data_target = TempTarget.GetData(),
	*data_source = Temp_Source_char.data(),
	*last_ptr_source = data_source + s_size_x * s_size_y - 1;

	while (data_source <= last_ptr_source) {
		*data_target = *data_source;
		*(data_target+1) = *data_source;
		*(data_target+2) = *data_source;

		data_source++;
		data_target = data_target+3;
	}

	if (s_size_x != t_size_x && s_size_y != t_size_y) {
		TempTarget = TempTarget.Rescale(t_size_x, t_size_y); // quality parameter optional
	}

	Target = TempTarget;
}

// Purpose:
// Return:
// Error:
void Tomography::reset_tomography( int size, int angles ) {
	_angles = angles;
	_size = size;

	_Sinogram.reset( _angles, _size );
	_Sinogram_ramp.reset( _angles, _size );
	_Slice_bp.reset( _size, _size );
	_Slice_fbp.reset( _size, _size );
	_Slice_iart.reset( _size, _size );
	_ImageBuffer.reset( 0, 0 );
}

// Purpose:
// Return:
// Error:
void Tomography::copy_wxImage_to_CImg(wxImage &Source, cimg_library::CImg<double> &Target){

	// Grey-scale computation only
	if (Target.spectrum() != 1)
		throw std::runtime_error("Berechnungsfehler: Es können nur Graustufen-Bilder "
		"verrechnet werden.");

	// 2D computation only
	if (Target.depth() != 1)
		throw std::runtime_error("Berechnungsfehler: Es können nur 2D-Bilder "
						"verrechnet werden.");

	int
	s_size_x = Source.GetWidth(),
	s_size_y = Source.GetHeight(),
	t_size_x = Target.width(),
	t_size_y = Target.height();

	cimg_library::CImg<unsigned char> TempTarget(s_size_x, s_size_y, 1, 1, 0);

	unsigned char
	*data_source = Source.GetData(),
	*data_target = TempTarget.data(),
	*last_ptr_source = data_source + s_size_x * s_size_y * 3 -1;

	while (data_source <= last_ptr_source - 2) {
		*data_target = 0.299 * *data_source + 0.587 * *(data_source + 1) + 0.114 * *(data_source + 2);
		data_target++;
		data_source = data_source + 3;
	}

	if (s_size_x != t_size_x && s_size_y != t_size_y) {
		TempTarget = TempTarget.resize(t_size_x, t_size_y, 2); // quality parameter optional
	}

	Target = TempTarget;
}

cimg_library::CImg<double> Tomography::correct_image( cimg_library::CImg<double> &image_data ){

	// Dirty fix to prevent logarithm problems
	image_data = image_data+1;

	wxCriticalSectionLocker enter( _i0CS );
	if( int(_i0) != 1)
		return -log( image_data ) + log( _i0 );
	else {
		double max_value;
		image_data.min_max( max_value );
		return -log( image_data ) + log( max_value );
	}
}

cimg_library::CImg<double> Tomography::interpolate_dead_pixels( cimg_library::CImg<double> &image_data ){
	cimg_library::CImg<double> ret( image_data );
	double dead_pixel_value = 1.0;
	cimg_forXY( ret,x,y ){
		if( cimg::abs( ret( x, y ) - dead_pixel_value ) < 3.0 ){

			if( x == 0 ){
				double replacement_value = dead_pixel_value;
				cimg_forX(ret, x2) {
					if( ret(x2, y) != dead_pixel_value ){
						replacement_value = ret(x2, y);
						break;
					}
					ret( x, y ) = replacement_value;
				}
			} else if( x == ret.width()-1 ) {
				double replacement_value = dead_pixel_value;
				cimg_forX(ret, x3) {
					if( ret(ret.width() -1 - x3, y) != dead_pixel_value ){
						replacement_value = ret(x3, y);
						break;
					}
					ret( x, y ) = replacement_value;
				}
			} else {
				double left_value = dead_pixel_value;
				double right_value = dead_pixel_value;

				// Determine right value
				for(int x4 = x; x4 < (int)ret._width; x4++){
					if( cimg::abs( ret( x4, y ) - dead_pixel_value ) > 3.0 ){
						right_value = ret(x4, y);
						break;
					}
				}

				// Determine left value
				for(int x4 = x; x4 >= 0; x4--){
					if( cimg::abs( ret( x4, y ) - dead_pixel_value ) > 3.0 ){
						left_value = ret(x4, y);
						break;
					}
				}
				ret(x , y) = left_value/2 + right_value/2;
			}
		}
	}
	return ret;
}

void Tomography::export_any_as_ascii(int ImageType, const char* filepath) {
	cimg_library::CImg<double> ToSave;
	switch (ImageType) {
	case Type_Sinogram:
		ToSave = _Sinogram.copy();
		if( ToSave.is_empty() )
			break;
		else {
			ToSave = correct_image( ToSave );
			//if( this->get_dead_pixel_correction() )
				//ToSave = interpolate_dead_pixels( ToSave );
		}
		break;
	case Type_Sinogram_ramp:
		ToSave = _Sinogram_ramp.copy();
		break;
	case Type_Slice_fbp:
		ToSave = _Slice_fbp.copy();
		break;
	case Type_Slice_bp:
		ToSave = _Slice_bp.copy();
		break;
	case Type_Slice_iart:
		ToSave = _Slice_iart.copy();
		break;
	case Type_Counts:
		ToSave = _Sinogram.copy();
		break;
	default:
		return;
	}

	if (ToSave.is_empty())
		return;
	ToSave.save_dlm(filepath);
}


// Purpose:
// Return:
// Error:
Tomography::TomoData::TomoData() : _Image(), _State(Tomography::NA), _Computed(false) {}

// Purpose:
// Return:
// Error:
cimg_library::CImg<double> Tomography::TomoData::copy() {
	wxCriticalSectionLocker enter(_ImageCS);
	return _Image;
}

// Purpose:
// Return:
// Error:
void Tomography::TomoData::paste(cimg_library::CImg<double>& NewData) {
	wxCriticalSectionLocker enter(_ImageCS);
	_Image = NewData;
}

// Purpose:
// Return:
// Error:
Tomography::enumImageState Tomography::TomoData::get_state() {
	wxCriticalSectionLocker enter(_StateCS);
	return _State;
}

// Purpose:
// Return:
// Error:
void Tomography::TomoData::set_state( Tomography::enumImageState NewImageState ) {
	wxCriticalSectionLocker enter(_StateCS);
	_State = NewImageState;
}

// Purpose:
// Return:
// Error:
bool Tomography::TomoData::is_computed() {
	wxCriticalSectionLocker enter(_ComputedCS);
	return _Computed;
}

// Purpose:
// Return:
// Error:
void Tomography::TomoData::is_computed(bool Value) {
	wxCriticalSectionLocker enter(_ComputedCS);
	_Computed = Value;
}

// Purpose:
// Return:
// Error:
void Tomography::TomoData::register_new_value(int pos, int angle, double Value) {
	// TODO Add boundary checking
	wxCriticalSectionLocker enter( _ImageCS );
	_Image(angle, pos) = Value;
}

void Tomography::set_rotation_axis( double value ){
	if( value < 0 || value > 1)
		return;
	wxCriticalSectionLocker enter( _rotation_centerCS );
	_rotation_center = value;
}

void Tomography::set_i0( int counts ){
	if( counts < 1 || counts > 20000) return;
	wxCriticalSectionLocker enter( _i0CS );
	_i0 = counts;
}

void Tomography::set_correct_dead_pixels( bool correct_pixels ){
	wxCriticalSectionLocker enter( _correct_dead_pixelsCS );
	_correct_dead_pixels = correct_pixels;
}

// Purpose:
// Return:
// Error:
void Tomography::TomoData::reset( int size_x, int size_y ) {
	wxCriticalSectionLocker enter1(_ImageCS);
	wxCriticalSectionLocker enter2(_ComputedCS);
	wxCriticalSectionLocker enter3(_StateCS);
	CImg<double> Temp( size_x, size_y, 1, 1, 0);
	_Image = Temp;
	_Computed = false;
	_State = Tomography::NA;
}
