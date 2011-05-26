static const char *RcsId = "$Id:  $";
//+=============================================================================
//
// file :        ClassFactory.cpp
//
// description : C++ source for the class_factory method of the DServer
//               device class. This method is responsible for the creation of
//               all class singleton for a device server. It is called
//               at device server startup
//
// project :     TANGO Device Server
//
// $Author:  $
//
// $Revision:  $
// $Date:  $
//
// SVN only:
// $HeadURL: $
//
// CVS only:
// $Source:  $
// $Log:  $
//
// copyleft :    European Synchrotron Radiation Facility
//               BP 220, Grenoble 38043
//               FRANCE
//
//-=============================================================================
//
//  		This file is generated by POGO
//	(Program Obviously used to Generate tango Object)
//
//         (c) - Software Engineering Group - ESRF
//=============================================================================


#include <tango.h>
#include <LimaDetectorClass.h>
#include <SimulatorCCDClass.h>

#ifdef BASLER_ENABLED
	#include <BaslerCCDClass.h>
#endif

#ifdef PILATUS_ENABLED
	#include <PilatusPixelDetectorClass.h>
#endif

#ifdef XPAD_ENABLED
	#include <XpadPixelDetectorClass.h>
#endif


/**
 *	Create LimaDetectorClass singleton and store it in DServer object.
 */

void Tango::DServer::class_factory()
{
	add_class(LimaDetector_ns::LimaDetectorClass::init("LimaDetector"));
	add_class(SimulatorCCD_ns::SimulatorCCDClass::init("SimulatorCCD"));
#ifdef BASLER_ENABLED
	add_class(BaslerCCD_ns::BaslerCCDClass::init("BaslerCCD"));
#endif

#ifdef PILATUS_ENABLED
	add_class(Pilatus_ns::PilatusClass::init("Pilatus"));
#endif

#ifdef XPAD_ENABLED	
	add_class(XpadPixelDetector_ns::XpadPixelDetectorClass::init("XpadPixelDetector"));
#endif
}
