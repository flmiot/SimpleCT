/// ---------------------------------------------------------------------------
// This file is part of SimpleCT. The SimpleCT software is in the public domain,
// furnished "as is", without technical support, and with no warranty, express or
// implied, as to its usefulness for any purpose.
//
// tomography.h
// Tomography class header file.
//
// Author: Florian Otte
// ---------------------------------------------------------------------------

#ifndef TOMOGRAPHY_H_
#define TOMOGRAPHY_H_

#define	MIN_TOMOGRAPHY_PIXELS 	16
#define MAX_TOMOGRAPHY_PIXELS 	512
#define MIN_TOMOGRAPHY_ANGLES 	16
#define MAX_TOMOGRAPHY_ANGLES 	512

#include "threads.h"

#include <wx/event.h>

#include "../ext/CImg.h"

class wxWindow;
class wxImage;
class wxString;

class Tomography : public CustomThreadClass {

	friend class ComputationThread;

public:
	Tomography( int size, int angles );
	~Tomography();

	void reset_tomography( int size, int angles );

	// Use internal image buffer for sinogram import and forward-projection
	void write_to_image_buffer( wxImage &Source );
	void load_sinogram_from_image_buffer();

	void load_sinogram_from_ascii_file( const char* filepath );

	// Computation & algorithms
	void compute_fwp_from_image_buffer();
	void compute_fbp( int FilterType );
	void compute_bp();
	void compute_iart() { return; } // TODO not yet implemented
	void abort_any_computation();

	// Register new reading (e.g. measured data)
	// This function is periodically called during measurement from outside the class
	struct Reading {
		double Angle;
		int Detectorpixel;
		int Value;
		bool Valid;
	};
	void register_new_reading( Reading &NewDataElement );

	// set position of rotation axis ( COR ? )
	void set_rotation_axis( double value );

	// set I0 (airscan - intensity)
	void set_i0( int counts );

	// Tell tomography to correct for dead pixels
	void set_correct_dead_pixels( bool correct_pixels );

	// Used whenever internal image data is to be displayed by the interface
	// Since internal pixel value range is much larger than 255, Windowing is implemented
	void export_any_as_wxImage( int ImageType, wxImage &Target,
			int MinPixelValue, int MaxPixelValue );

	// Data export (export any image data to ASCII text format)
	void export_any_as_ascii( int ImageType, const char* filepath );

	// Getters
	bool is_any_computed(int ImageType);
	int get_any_image_state(int ImageType);
	int get_tomography_size();
	int get_tomography_angles();
	int get_current_computation();
	double get_current_computation_progress();
	bool get_dead_pixel_correction();

	/* Delete as soon as possible
	// start computation thread
	int start_fwp(wxString &ImageName);
	int start_fbp(int Filter);
	int start_iart(){ return 1;}
	*/

	// A few enum declarations for convenience
	enum enumImageState { NA, NoChanges, Updated, Is_Currently_In_Use };
	enum enumImageType { Type_Sinogram = 0, Type_Sinogram_ramp = 1,
		Type_Slice_fbp, Type_Slice_bp, Type_Slice_iart, Type_Counts };
	enum enumFiltering { None, Ramp };
	enum enumComputation { none, fwp, fbp, bp, iart };

protected:

	// Basic encapsulation class for tomography image data
	// This class makes extensive use of copying, but
	// provides a (thread-)safe way to access data
	class TomoData {
	public:
		TomoData();
		cimg_library::CImg<double> copy();
		void paste(cimg_library::CImg<double> &NewData);
		enumImageState get_state();
		void set_state(enumImageState NewImageState);
		bool is_computed();
		void is_computed(bool Value);
		void register_new_value(int pos, int angle, double Value);
		void reset( int size_x, int size_y );
	private:
		cimg_library::CImg<double> _Image;
		wxCriticalSection _ImageCS;
		enumImageState _State;
		wxCriticalSection _StateCS;
		bool _Computed;
		wxCriticalSection _ComputedCS;
	};
	TomoData _Sinogram,
	_Sinogram_ramp,
	_Slice_fbp,
	_Slice_bp,
	_Slice_iart,
	_ImageBuffer;

	// Implemented CustomThreadClass methods for background computation
	wxThread::ExitCode Task();
	void OnThread_DestructorCall();

	// The threadfunc methods are called from secondary thread-
	// context for background computation
	wxThread::ExitCode threadfunc_compute_fwp();
	wxThread::ExitCode threadfunc_compute_fbp();
	wxThread::ExitCode threadfunc_compute_bp();
	wxThread::ExitCode threadfunc_compute_iart(); // TODO not yet implemented
	void threadfunc_filter_sinogram();

	// Setters
	void set_computation_progress( double Progress );
	void set_current_computation( enumComputation Computation );
	void setImageState( int Type, int State );

	// Internal image conversion
	void copy_CImg_to_wxImage( cimg_library::CImg<double> &Source, wxImage &Target,
						int MinPixelValue, int MaxPixelValue );
	void copy_wxImage_to_CImg( wxImage &Source, cimg_library::CImg<double> &Target );

	// Correction for absorption and pure beam intensity
	cimg_library::CImg<double> correct_image( cimg_library::CImg<double> &image_data );

	// Dead pixel interpolation
	// Should only be called on images containing pure count data
	cimg_library::CImg<double> interpolate_dead_pixels( cimg_library::CImg<double> &image_data);

	// Tomography size and angles
	int _size, _angles;

	// Computation & thread safety
	int _currentComputation;
	wxCriticalSection _currentComputationCS;
	double _progress_computation;
	wxCriticalSection _progress_computationCS;
	enumFiltering _CurrentFilter;

	double _rotation_center;
	wxCriticalSection _rotation_centerCS;
	int _i0;
	wxCriticalSection _i0CS;

	bool _correct_dead_pixels;
	wxCriticalSection _correct_dead_pixelsCS;

};

// the ID we'll use to identify our event
const int COMPUTATION_SUCCESSFULL_ID = 100000;
const int COMPUTATION_ERROR_ID = 100001;
const int COMPUTATION_UPDATED_ID = 100002;

DECLARE_EVENT_TYPE(COMPUTATION_SUCCESSFULL_EVENT,  wxCommandEvent)
DECLARE_EVENT_TYPE(COMPUTATION_ERROR_EVENT,  wxCommandEvent)
DECLARE_EVENT_TYPE(COMPUTATION_UPDATED_ID,  wxCommandEvent)



#endif /* TOMOGRAPHY_H_ */
