//+=============================================================================
//
// file :         Factory.cpp
//
// description : Include for Factory.cpp
//
// copyleft :    Synchrotron SOLEIL
//               L'Orme des merisiers - Saint Aubin
//               BP48 - 91192 Gif sur Yvette
//               FRANCE
//
//-=============================================================================
#ifndef _FACTORY_H_
#define _FACTORY_H_

#include <tango.h>

#include <Singleton.h>

#include <HwInterface.h>
#include <CtControl.h>
#include "Debug.h"
#include <yat/threading/Mutex.h>


#ifdef SIMULATOR_ENABLED
#include <SimulatorInterface.h>
#endif

#ifdef AVIEX_ENABLED  
#include <AviexCamera.h>
#include <AviexDetInfoCtrlObj.h>
#include <AviexSyncCtrlObj.h>
#include <AviexRoiCtrlObj.h>
#include <AviexBinCtrlObj.h>
#include <AviexInterface.h>
#endif

#ifdef BASLER_ENABLED  
#include <BaslerInterface.h>
#include <BaslerCamera.h>
#endif

#ifdef XPAD_ENABLED
#include <XpadInterface.h>
#endif

#ifdef PILATUS_ENABLED
#include <PilatusInterface.h>
#endif

#ifdef MARCCD_ENABLED
#include <MarccdInterface.h>
#endif

#ifdef ADSC_ENABLED
#include <AdscInterface.h>
#endif

#ifdef PROSILICA_ENABLED
#include <ProsilicaInterface.h>
#include <ProsilicaCamera.h>
#include <ProsilicaDetInfoCtrlObj.h>
#include <ProsilicaBufferCtrlObj.h>
#include <ProsilicaVideoCtrlObj.h>
#include <ProsilicaSyncCtrlObj.h>   
#endif

#ifdef ANDOR_ENABLED
#include <AndorInterface.h>
#endif

#ifdef PRINCETON_ENABLED
#include <RoperScientificCamera.h>
#include <RoperScientificBinCtrlObj.h>
#include <RoperScientificDetInfoCtrlObj.h>
#include <RoperScientificRoiCtrlObj.h>
#include <RoperScientificSyncCtrlObj.h>   
#include <RoperScientificInterface.h>
#endif

#ifdef PCO_ENABLED
#include <Pco.h>
#include <PcoBufferCtrlObj.h>
#include <PcoCamera.h>
#include <PcoCameraUtils.h>
#include <PcoDetInfoCtrlObj.h>
#include <PcoInterface.h>
#include <PcoSyncCtrlObj.h>   
#endif

#ifdef PERKINELMER_ENABLED
#include <PerkinElmerBinCtrlObj.h>
#include <PerkinElmerCompatibility.h>
#include <PerkinElmerDetInfoCtrlObj.h>
#include <PerkinElmerInterface.h>
#include <PerkinElmerSyncCtrlObj.h>    
#endif

#ifdef ANDOR3_ENABLED
#include <Andor3BinCtrlObj.h>
#include <Andor3Camera.h>
#include <Andor3DetInfoCtrlObj.h>
#include <Andor3Interface.h>
#include <Andor3RoiCtrlObj.h>
#include <Andor3ShutterCtrlObj.h>
#include <Andor3SyncCtrlObj.h>    
#endif


#ifdef VIEWORKSVP_ENABLED
#include <VieworksVPBinCtrlObj.h>
#include <VieworksVPCamera.h>
#include <VieworksVPDetInfoCtrlObj.h>
#include <VieworksVPInterface.h>
#include <VieworksVPRoiCtrlObj.h>
#include <VieworksVPShutterCtrlObj.h>
#include <VieworksVPSyncCtrlObj.h>    
#endif

#ifdef HAMAMATSU_ENABLED
#include <HamamatsuCamera.h>
#include <HamamatsuBinCtrlObj.h>
#include <HamamatsuDetInfoCtrlObj.h>
#include <HamamatsuRoiCtrlObj.h>
#include <HamamatsuSyncCtrlObj.h>   
#include <HamamatsuInterface.h>
#endif

#ifdef EIGER_ENABLED
#include <EigerCamera.h>
#include <EigerDetInfoCtrlObj.h>
#include <EigerSyncCtrlObj.h>
#include <EigerInterface.h>
#endif

#ifdef UVIEW_ENABLED
#include <UviewBinCtrlObj.h>
#include <UviewCamera.h>
#include <UviewDetInfoCtrlObj.h>
#include <UviewInterface.h>
#include <UviewRoiCtrlObj.h>
#endif

using namespace lima;

class ControlFactory : public Singleton<ControlFactory>
{
public:

    //create the main object of Lima CtConttrol
    CtControl* create_control(const std::string& detector_type);

    //get the main object of Lima CtConttrol
    CtControl* get_control(const std::string& type = "");

    //initialize all pointers
    void reset(const std::string& detector_type);

    //init the specific device, necessary when user call Init on generic device
    void init_specific_device(const std::string& detector_type);

    //get the state in a AutoMutex lock
    Tango::DevState get_state(void);

    //get the status in a AutoMutex lock
    std::string get_status(void);

    //fix the state in a AutoMutex lock
    void set_state(Tango::DevState state);

    //fix the status in a AutoMutex lock
    void set_status(const std::string& status);

    //return to the client the global mutex, in order to use ctControl in a scoped lock
    yat::Mutex& get_global_mutex();

private:
    void initialize();


    void*                           m_camera;      //generic pointer, must be casted to real XXX::Camera when using it !
    void*                           m_interface;   //generic pointer, must be casted to real XXX::Interface when using it !
    CtControl*                      m_control;     //the main object of Lima

    static bool                     m_is_created;
    std::string                     m_server_name;
    std::string                     m_device_name_specific;
#ifdef LAYOUT_ENABLED    
    std::string                     m_device_name_layout;
#endif    
#ifdef ROICOUNTERS_ENABLED    
    std::string                     m_device_name_roicounters;
#endif        
    Tango::DevState                 m_state;
    stringstream                    m_status;

    //lock the singleton acess
    yat::Mutex                      object_control_lock;

    //lock the singleton acess
    yat::Mutex                      object_state_lock;

} ;

#endif
