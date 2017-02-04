# SimpleCT
A simple gui for custom tomography setups with the PYHWE 09058-50 X-ray-device and Arduino Leonardo. 

## Purpose
- control PHYWE 09058-50 X-ray-device (Voltage, Current, Readout)
- capture and store GM counter countrates 
- tell Arduino Leonardo (which is running the MOHFA - software) where to move the stage stepper motors
- reconstruct tomography slices from captured count data and let the user save all results

## Third party components
- the wxWidgets framework. Used for almost anything gui related. 
- the CImg-Library by David Tschumperle et al. 
- the boost-libraries Smart Ptr and Asio 
