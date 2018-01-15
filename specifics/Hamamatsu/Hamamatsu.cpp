static const char *RcsId = "$Id:  $";
//+=============================================================================
//
// file :         Hamamatsu.cpp
//
// description :  C++ source for the Hamamatsu and its commands.
//                The class is derived from Device. It represents the
//                CORBA servant object which will be accessed from the
//                network. All commands which can be executed on the
//                Hamamatsu are implemented in this file.
//
// project :      TANGO Device Server
//
// $Author:  $
//
// $Revision:  $
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
// copyleft :    Synchrotron SOLEIL
//               L'Orme des merisiers - Saint Aubin
//               BP48 - 91192 Gif sur Yvette
//               FRANCE
//
//-=============================================================================
//
//  		This file is generated by POGO
//	(Program Obviously used to Generate tango Object)
//
//         (c) - Software Engineering Group - ESRF
//=============================================================================



//===================================================================
//
//	The following table gives the correspondence
//	between commands and method name.
//
//  Command name|  Method name
//	----------------------------------------
//  State   |  dev_state()
//  Status  |  dev_status()
//
//===================================================================


#include "tango.h"
#include <PogoHelper.h>
#include <Hamamatsu.h>
#include <HamamatsuClass.h>

#define MAX_ATTRIBUTE_STRING_LENGTH 256
#define READOUTSPEED_NORMAL_VALUE		2
#define READOUTSPEED_SLOW_VALUE			1
#define READOUTSPEED_NORMAL_NAME	"NORMAL"
#define READOUTSPEED_SLOW_NAME		"SLOW"

#define SYNCREADOUT_BLANKMODE_STANDARD	"STANDARD"
#define SYNCREADOUT_BLANKMODE_MINIMUM	"MINIMUM"


namespace Hamamatsu_ns
{

//+----------------------------------------------------------------------------
//
// method : 		Hamamatsu::Hamamatsu(string &s)
//
// description : 	constructor for simulated Hamamatsu
//
// in : - cl : Pointer to the DeviceClass object
//      - s : Device name
//
//-----------------------------------------------------------------------------
Hamamatsu::Hamamatsu(Tango::DeviceClass *cl,string &s)
:Tango::Device_4Impl(cl,s.c_str())
{
	init_device();
}

Hamamatsu::Hamamatsu(Tango::DeviceClass *cl,const char *s)
:Tango::Device_4Impl(cl,s)
{
	init_device();
}

Hamamatsu::Hamamatsu(Tango::DeviceClass *cl,const char *s,const char *d)
:Tango::Device_4Impl(cl,s,d)
{
	init_device();
}
//+----------------------------------------------------------------------------
//
// method : 		Hamamatsu::delete_device()
//
// description : 	will be called at device destruction or at init command.
//
//-----------------------------------------------------------------------------
void Hamamatsu::delete_device()
{
	//	Delete device allocated objects

	DELETE_DEVSTRING_ATTRIBUTE(attr_readoutSpeed_read);
	DELETE_SCALAR_ATTRIBUTE(attr_lostFrames_read);
	DELETE_SCALAR_ATTRIBUTE(attr_fps_read);
    DELETE_SCALAR_ATTRIBUTE(attr_wViewEnabled_read);
	DELETE_SCALAR_ATTRIBUTE(attr_topViewExposureTime_read);
	DELETE_SCALAR_ATTRIBUTE(attr_bottomViewExposureTime_read);
    DELETE_SCALAR_ATTRIBUTE(attr_Temperature_read);
}

//+----------------------------------------------------------------------------
//
// method : 		Hamamatsu::init_device()
//
// description : 	will be called at device initialization.
//
//-----------------------------------------------------------------------------
void Hamamatsu::init_device()
{
	INFO_STREAM << "Hamamatsu::Hamamatsu() create device " << device_name << endl;

	// Initialise variables to default values
	//--------------------------------------------
	get_device_property();

	CREATE_DEVSTRING_ATTRIBUTE(attr_readoutSpeed_read, MAX_ATTRIBUTE_STRING_LENGTH);
	CREATE_SCALAR_ATTRIBUTE(attr_lostFrames_read);
	CREATE_SCALAR_ATTRIBUTE(attr_fps_read);
	CREATE_SCALAR_ATTRIBUTE(attr_wViewEnabled_read);
	CREATE_SCALAR_ATTRIBUTE(attr_topViewExposureTime_read);
	CREATE_SCALAR_ATTRIBUTE(attr_bottomViewExposureTime_read);
	CREATE_SCALAR_ATTRIBUTE(attr_Temperature_read);

	m_is_device_initialized = false;
	set_state(Tango::INIT);
	m_status_message.str("");

	try
	{
		//- get the main object used to pilot the lima framework		
		m_ct = ControlFactory::instance().get_control("Hamamatsu");
		
		//- get interface to specific camera
		m_hw = dynamic_cast<lima::Hamamatsu::Interface*>(m_ct->hwInterface());
		
		//- get camera to specific detector
		m_camera = &(m_hw->getCamera());

	}
	catch(Exception& e)
	{
		INFO_STREAM << "Initialization Failed : " << e.getErrMsg() << endl;
		m_status_message << "Initialization Failed : " << e.getErrMsg( ) << endl;
		m_is_device_initialized = false;
		set_state(Tango::FAULT);
		return;
	}
	catch(...)
	{
		INFO_STREAM << "Initialization Failed : UNKNOWN" << endl;
		m_status_message << "Initialization Failed : UNKNOWN" << endl;
		set_state(Tango::FAULT);
		m_is_device_initialized = false;
		return;
	}
	
	// write at init
    //------------------------------------------------------------------------------
    // Readout Speed
    //------------------------------------------------------------------------------
	try
	{      		
		//write Readout Speed
		INFO_STREAM << "Write tango hardware at Init - readoutSpeed." << endl;
		Tango::WAttribute &readoutSpeed = dev_attr->get_w_attr_by_name("readoutSpeed");
		m_readoutSpeed = memorizedReadoutSpeed;
		strcpy(*attr_readoutSpeed_read, memorizedReadoutSpeed.c_str());
		readoutSpeed.set_write_value(m_readoutSpeed);
		write_readoutSpeed(readoutSpeed);
	}
	catch(Exception& e)
	{
		INFO_STREAM << "Initialization Failed : " << e.getErrMsg() << endl;
		m_status_message << "Initialization Failed : " << e.getErrMsg( ) << endl;
		m_is_device_initialized = false;
		set_state(Tango::FAULT);
		return;
	}
	catch(...)
	{
		INFO_STREAM << "Initialization Failed : UNKNOWN" << endl;
		m_status_message << "Initialization Failed : UNKNOWN" << endl;
		set_state(Tango::FAULT);
		m_is_device_initialized = false;
		return;
	}

    //------------------------------------------------------------------------------
    // Synchronous readout blank mode
    //------------------------------------------------------------------------------
	try
	{      		
		//Synchronous readout blank mode
		INFO_STREAM << "Write tango hardware at Init - BlankOfSyncreadoutTrigger." << endl;

		transform(blankOfSyncreadoutTrigger.begin(), blankOfSyncreadoutTrigger.end(), blankOfSyncreadoutTrigger.begin(), ::toupper);

        if (blankOfSyncreadoutTrigger != SYNCREADOUT_BLANKMODE_STANDARD &&
            blankOfSyncreadoutTrigger != SYNCREADOUT_BLANKMODE_MINIMUM)
		{			
			string userMsg;
            userMsg = string("Available Synchronous Readout blank modes are:\n- ") + string(SYNCREADOUT_BLANKMODE_STANDARD) + string("\n- ") + string(SYNCREADOUT_BLANKMODE_MINIMUM);

            Tango::Except::throw_exception(	"CONFIGURATION_ERROR",
                                            userMsg.c_str(),
                                            "Hamamatsu::init_device");
		}

        m_SyncreadoutBlankMode = lima::Hamamatsu::Camera::SyncReadOut_BlankMode_Standard;

        if (blankOfSyncreadoutTrigger == SYNCREADOUT_BLANKMODE_STANDARD)
            m_SyncreadoutBlankMode = lima::Hamamatsu::Camera::SyncReadOut_BlankMode_Standard;
        else
        if (blankOfSyncreadoutTrigger == SYNCREADOUT_BLANKMODE_MINIMUM)
            m_SyncreadoutBlankMode = lima::Hamamatsu::Camera::SyncReadOut_BlankMode_Minimum;
		
		m_camera->setSyncReadoutBlankMode(m_SyncreadoutBlankMode);
	}
	catch(Exception& e)
	{
		INFO_STREAM << "Initialization Failed : " << e.getErrMsg() << endl;
		m_status_message << "Initialization Failed : " << e.getErrMsg( ) << endl;
		m_is_device_initialized = false;
		set_state(Tango::FAULT);
		return;
	}
	catch(...)
	{
		INFO_STREAM << "Initialization Failed : UNKNOWN" << endl;
		m_status_message << "Initialization Failed : UNKNOWN" << endl;
		set_state(Tango::FAULT);
		m_is_device_initialized = false;
		return;
	}

    //------------------------------------------------------------------------------
    // Top View & Bottom View Exposure Times
    //------------------------------------------------------------------------------
    m_TopViewExposureTime    = memorizedTopViewExposureTime   ;
    m_BottomViewExposureTime = memorizedBottomViewExposureTime;

    //------------------------------------------------------------------------------
    // W-View Mode
    //------------------------------------------------------------------------------
	try
	{      		
		INFO_STREAM << "Write tango hardware at Init - wViewEnabled." << endl;
		Tango::WAttribute &wiewMode = dev_attr->get_w_attr_by_name("wViewEnabled");
		m_wViewEnabled = memorizedWViewEnabled;
        *attr_wViewEnabled_read = m_wViewEnabled;
		wiewMode.set_write_value(m_wViewEnabled);
		write_wViewEnabled(wiewMode);
	}
	catch(Exception& e)
	{
		INFO_STREAM << "Initialization Failed : " << e.getErrMsg() << endl;
		m_status_message << "Initialization Failed : " << e.getErrMsg( ) << endl;
		m_is_device_initialized = false;
		set_state(Tango::FAULT);
		return;
	}
	catch(...)
	{
		INFO_STREAM << "Initialization Failed : UNKNOWN" << endl;
		m_status_message << "Initialization Failed : UNKNOWN" << endl;
		set_state(Tango::FAULT);
		m_is_device_initialized = false;
    	dev_state();	
		return;
	}

    //------------------------------------------------------------------------------
    // Top View Exposure Time
    //------------------------------------------------------------------------------
    try
    {      		
	    INFO_STREAM << "Write tango hardware at Init - topViewExposureTime." << endl;
	    Tango::WAttribute &topViewExposure = dev_attr->get_w_attr_by_name("topViewExposureTime");
        *attr_topViewExposureTime_read = m_TopViewExposureTime;
	    topViewExposure.set_write_value(m_TopViewExposureTime);
    }
    catch(Exception& e)
    {
	    INFO_STREAM << "Initialization Failed : " << e.getErrMsg() << endl;
	    m_status_message << "Initialization Failed : " << e.getErrMsg( ) << endl;
	    m_is_device_initialized = false;
	    set_state(Tango::FAULT);
	    return;
    }
    catch(...)
    {
	    INFO_STREAM << "Initialization Failed : UNKNOWN" << endl;
	    m_status_message << "Initialization Failed : UNKNOWN" << endl;
	    set_state(Tango::FAULT);
	    m_is_device_initialized = false;
	    return;
    }

    //------------------------------------------------------------------------------
    // Bottom View Exposure Time
    //------------------------------------------------------------------------------
    try
    {      		
	    INFO_STREAM << "Write tango hardware at Init - bottomViewExposureTime." << endl;
	    Tango::WAttribute &bottomViewExposure = dev_attr->get_w_attr_by_name("bottomViewExposureTime");
        *attr_bottomViewExposureTime_read = m_BottomViewExposureTime;
	    bottomViewExposure.set_write_value(m_BottomViewExposureTime);
    }
    catch(Exception& e)
    {
	    INFO_STREAM << "Initialization Failed : " << e.getErrMsg() << endl;
	    m_status_message << "Initialization Failed : " << e.getErrMsg( ) << endl;
	    m_is_device_initialized = false;
	    set_state(Tango::FAULT);
	    return;
    }
    catch(...)
    {
	    INFO_STREAM << "Initialization Failed : UNKNOWN" << endl;
	    m_status_message << "Initialization Failed : UNKNOWN" << endl;
	    set_state(Tango::FAULT);
	    m_is_device_initialized = false;
	    return;
    }

	m_is_device_initialized = true;
	set_state(Tango::STANDBY);
	dev_state();	
}


//+----------------------------------------------------------------------------
//
// method : 		Hamamatsu::get_device_property()
//
// description : 	Read the device properties from database.
//
//-----------------------------------------------------------------------------
void Hamamatsu::get_device_property()
{
	//	Initialize your default values here (if not done with  POGO).
	//------------------------------------------------------------------

	//	Read device properties from database.(Automatic code generation)
	//------------------------------------------------------------------
	Tango::DbData	dev_prop;
	dev_prop.push_back(Tango::DbDatum("DetectorNum"));
	dev_prop.push_back(Tango::DbDatum("MemorizedReadoutSpeed"));
	dev_prop.push_back(Tango::DbDatum("BlankOfSyncreadoutTrigger"));
	dev_prop.push_back(Tango::DbDatum("MemorizedTopViewExposureTime"));
	dev_prop.push_back(Tango::DbDatum("MemorizedBottomViewExposureTime"));
	dev_prop.push_back(Tango::DbDatum("MemorizedWViewEnabled"));

	//	Call database and extract values
	//--------------------------------------------
	if (Tango::Util::instance()->_UseDb==true)
		get_db_device()->get_property(dev_prop);
	Tango::DbDatum	def_prop, cl_prop;
	HamamatsuClass	*ds_class =
		(static_cast<HamamatsuClass *>(get_device_class()));
	int	i = -1;

	//	Try to initialize DetectorNum from class property
	cl_prop = ds_class->get_class_property(dev_prop[++i].name);
	if (cl_prop.is_empty()==false)	cl_prop  >>  detectorNum;
	else {
		//	Try to initialize DetectorNum from default device value
		def_prop = ds_class->get_default_device_property(dev_prop[i].name);
		if (def_prop.is_empty()==false)	def_prop  >>  detectorNum;
	}
	//	And try to extract DetectorNum value from database
	if (dev_prop[i].is_empty()==false)	dev_prop[i]  >>  detectorNum;

	//	Try to initialize MemorizedReadoutSpeed from class property
	cl_prop = ds_class->get_class_property(dev_prop[++i].name);
	if (cl_prop.is_empty()==false)	cl_prop  >>  memorizedReadoutSpeed;
	else {
		//	Try to initialize MemorizedReadoutSpeed from default device value
		def_prop = ds_class->get_default_device_property(dev_prop[i].name);
		if (def_prop.is_empty()==false)	def_prop  >>  memorizedReadoutSpeed;
	}
	//	And try to extract MemorizedReadoutSpeed value from database
	if (dev_prop[i].is_empty()==false)	dev_prop[i]  >>  memorizedReadoutSpeed;

	//	Try to initialize BlankOfSyncreadoutTrigger from class property
	cl_prop = ds_class->get_class_property(dev_prop[++i].name);
	if (cl_prop.is_empty()==false)	cl_prop  >>  blankOfSyncreadoutTrigger;
	else {
		//	Try to initialize BlankOfSyncreadoutTrigger from default device value
		def_prop = ds_class->get_default_device_property(dev_prop[i].name);
		if (def_prop.is_empty()==false)	def_prop  >>  blankOfSyncreadoutTrigger;
	}
	//	And try to extract BlankOfSyncreadoutTrigger value from database
	if (dev_prop[i].is_empty()==false)	dev_prop[i]  >>  blankOfSyncreadoutTrigger;

	//	Try to initialize MemorizedTopViewExposureTime from class property
	cl_prop = ds_class->get_class_property(dev_prop[++i].name);
	if (cl_prop.is_empty()==false)	cl_prop  >>  memorizedTopViewExposureTime;
	else {
		//	Try to initialize MemorizedTopViewExposureTime from default device value
		def_prop = ds_class->get_default_device_property(dev_prop[i].name);
		if (def_prop.is_empty()==false)	def_prop  >>  memorizedTopViewExposureTime;
	}
	//	And try to extract MemorizedTopViewExposureTime value from database
	if (dev_prop[i].is_empty()==false)	dev_prop[i]  >>  memorizedTopViewExposureTime;

	//	Try to initialize MemorizedBottomViewExposureTime from class property
	cl_prop = ds_class->get_class_property(dev_prop[++i].name);
	if (cl_prop.is_empty()==false)	cl_prop  >>  memorizedBottomViewExposureTime;
	else {
		//	Try to initialize MemorizedBottomViewExposureTime from default device value
		def_prop = ds_class->get_default_device_property(dev_prop[i].name);
		if (def_prop.is_empty()==false)	def_prop  >>  memorizedBottomViewExposureTime;
	}
	//	And try to extract MemorizedBottomViewExposureTime value from database
	if (dev_prop[i].is_empty()==false)	dev_prop[i]  >>  memorizedBottomViewExposureTime;

	//	Try to initialize MemorizedWViewEnabled from class property
	cl_prop = ds_class->get_class_property(dev_prop[++i].name);
	if (cl_prop.is_empty()==false)	cl_prop  >>  memorizedWViewEnabled;
	else {
		//	Try to initialize MemorizedWViewEnabled from default device value
		def_prop = ds_class->get_default_device_property(dev_prop[i].name);
		if (def_prop.is_empty()==false)	def_prop  >>  memorizedWViewEnabled;
	}
	//	And try to extract MemorizedWViewEnabled value from database
	if (dev_prop[i].is_empty()==false)	dev_prop[i]  >>  memorizedWViewEnabled;



	//	End of Automatic code generation
	//------------------------------------------------------------------
	yat4tango::PropertyHelper::create_property_if_empty(this, dev_prop, "0", "DetectorNum");
    yat4tango::PropertyHelper::create_property_if_empty(this, dev_prop, "NORMAL", "MemorizedReadoutSpeed");
	yat4tango::PropertyHelper::create_property_if_empty(this, dev_prop, SYNCREADOUT_BLANKMODE_STANDARD, "BlankOfSyncreadoutTrigger");

	yat4tango::PropertyHelper::create_property_if_empty(this, dev_prop, "false", "MemorizedWViewEnabled"          );
	yat4tango::PropertyHelper::create_property_if_empty(this, dev_prop, "1000" , "MemorizedTopViewExposureTime"   );
	yat4tango::PropertyHelper::create_property_if_empty(this, dev_prop, "1000" , "MemorizedBottomViewExposureTime");
}

//+----------------------------------------------------------------------------
//
// method : 		Hamamatsu::always_executed_hook()
//
// description : 	method always executed before any command is executed
//
//-----------------------------------------------------------------------------
void Hamamatsu::always_executed_hook()
{
    try
    {
        m_status_message.str("");
        //- get the singleton control objet used to pilot the lima framework
		m_ct = ControlFactory::instance().get_control("Hamamatsu");
		
		//- get interface to specific camera
		m_hw = dynamic_cast<lima::Hamamatsu::Interface*>(m_ct->hwInterface());
		
		//- get camera to specific detector
		m_camera = &(m_hw->getCamera());
		
		//update state
        dev_state();
	}
    catch (Exception& e)
    {
        ERROR_STREAM << e.getErrMsg() << endl;
        m_status_message << "Initialization Failed : " << e.getErrMsg() << endl;
        //- throw exception
        set_state(Tango::FAULT);
        m_is_device_initialized = false;
        return;
    }
    catch (...)
    {
        ERROR_STREAM << "Initialization Failed : UNKNOWN" << endl;
        m_status_message << "Initialization Failed : UNKNOWN" << endl;
        //- throw exception
        set_state(Tango::FAULT);
        m_is_device_initialized = false;
        return;
    }
}
//+----------------------------------------------------------------------------
//
// method : 		Hamamatsu::read_attr_hardware
//
// description : 	Hardware acquisition for attributes.
//
//-----------------------------------------------------------------------------
void Hamamatsu::read_attr_hardware(vector<long> &attr_list)
{
	DEBUG_STREAM << "Hamamatsu::read_attr_hardware(vector<long> &attr_list) entering... "<< endl;
	//	Add your own code here
}
//+----------------------------------------------------------------------------
//
// method : 		Hamamatsu::read_Temperature
// 
// description : 	Extract real attribute values for Temperature acquisition result.
//
//-----------------------------------------------------------------------------
void Hamamatsu::read_Temperature(Tango::Attribute &attr)
{
	DEBUG_STREAM << "Hamamatsu::read_Temperature(Tango::Attribute &attr) entering... "<< endl;
    
	try
	{
		double temperature = 0.0;
        bool   NotSupported;

        temperature = m_camera->getSensorTemperature(NotSupported);
		*attr_Temperature_read = (Tango::DevDouble)temperature;
		attr.set_value  (attr_Temperature_read);
        attr.set_quality((NotSupported) ? Tango::ATTR_INVALID : Tango::ATTR_VALID);
	}
	catch(Tango::DevFailed& df)
	{
		ERROR_STREAM << df << endl;
		//- rethrow exception
		Tango::Except::re_throw_exception(df,
                                          "TANGO_DEVICE_ERROR",
                                          string(df.errors[0].desc).c_str(),
                                          "Hamamatsu::read_Temperature");
	}
	catch(Exception& e)
	{
		ERROR_STREAM << e.getErrMsg() << endl;
		//- throw exception
        Tango::Except::throw_exception("TANGO_DEVICE_ERROR",
                                       e.getErrMsg().c_str(),
                                       "Hamamatsu::read_Temperature");
	}
}

//+----------------------------------------------------------------------------
//
// method : 		Hamamatsu::read_topViewExposureTime
// 
// description : 	Extract real attribute values for topViewExposureTime acquisition result.
//
//-----------------------------------------------------------------------------
void Hamamatsu::read_topViewExposureTime(Tango::Attribute &attr)
{
	DEBUG_STREAM << "Hamamatsu::read_topViewExposureTime(Tango::Attribute &attr) entering... "<< endl;

	try
	{
		double exptime = 0.0;

        m_camera->getViewExpTime1(exptime);
		*attr_topViewExposureTime_read = (Tango::DevDouble)(exptime * 1000.0);
		attr.set_value(attr_topViewExposureTime_read);
	}
	catch(Tango::DevFailed& df)
	{
		ERROR_STREAM << df << endl;
		//- rethrow exception
		Tango::Except::re_throw_exception(df,
                                          "TANGO_DEVICE_ERROR",
                                          string(df.errors[0].desc).c_str(),
                                          "Hamamatsu::read_topViewExposureTime");
	}
	catch(Exception& e)
	{
		ERROR_STREAM << e.getErrMsg() << endl;
		//- throw exception
        Tango::Except::throw_exception("TANGO_DEVICE_ERROR",
                                       e.getErrMsg().c_str(),
                                       "Hamamatsu::read_topViewExposureTime");
	}
}

//+----------------------------------------------------------------------------
//
// method : 		Hamamatsu::write_topViewExposureTime
// 
// description : 	Write topViewExposureTime attribute values to hardware.
//
//-----------------------------------------------------------------------------
void Hamamatsu::write_topViewExposureTime(Tango::WAttribute &attr)
{
	DEBUG_STREAM << "Hamamatsu::write_topViewExposureTime(Tango::WAttribute &attr) entering... "<< endl;

	try
	{
        attr.get_write_value(attr_topViewExposureTime_write);
        m_camera->setViewExpTime1((double) (attr_topViewExposureTime_write / 1000.0));

        m_TopViewExposureTime = (double)attr_topViewExposureTime_write;
		PropertyHelper::set_property(this, "MemorizedTopViewExposureTime", m_TopViewExposureTime);
	}
	catch(Tango::DevFailed& df)
	{
		ERROR_STREAM << df << endl;
		//- rethrow exception
		Tango::Except::re_throw_exception(df,
                                          "TANGO_DEVICE_ERROR",
                                          string(df.errors[0].desc).c_str(),
                                          "Hamamatsu::write_topViewExposureTime");
	}
	catch(Exception& e)
	{
		ERROR_STREAM << e.getErrMsg() << endl;
		//- throw exception
        Tango::Except::throw_exception("TANGO_DEVICE_ERROR",
                                       e.getErrMsg().c_str(),
                                       "Hamamatsu::write_topViewExposureTime");
	}	
}

//+----------------------------------------------------------------------------
//
// method : 		Hamamatsu::read_bottomViewExposureTime
// 
// description : 	Extract real attribute values for bottomViewExposureTime acquisition result.
//
//-----------------------------------------------------------------------------
void Hamamatsu::read_bottomViewExposureTime(Tango::Attribute &attr)
{
	DEBUG_STREAM << "Hamamatsu::read_bottomViewExposureTime(Tango::Attribute &attr) entering... "<< endl;

	try
	{
		double exptime = 0.0;

        m_camera->getViewExpTime2(exptime);
		*attr_bottomViewExposureTime_read = (Tango::DevDouble)(exptime * 1000.0);
		attr.set_value(attr_bottomViewExposureTime_read);
	}
	catch(Tango::DevFailed& df)
	{
		ERROR_STREAM << df << endl;
		//- rethrow exception
		Tango::Except::re_throw_exception(df,
                                          "TANGO_DEVICE_ERROR",
                                          string(df.errors[0].desc).c_str(),
                                          "Hamamatsu::read_bottomViewExposureTime");
	}
	catch(Exception& e)
	{
		ERROR_STREAM << e.getErrMsg() << endl;
		//- throw exception
        Tango::Except::throw_exception("TANGO_DEVICE_ERROR",
                                       e.getErrMsg().c_str(),
                                       "Hamamatsu::read_bottomViewExposureTime");
	}
}

//+----------------------------------------------------------------------------
//
// method : 		Hamamatsu::write_bottomViewExposureTime
// 
// description : 	Write bottomViewExposureTime attribute values to hardware.
//
//-----------------------------------------------------------------------------
void Hamamatsu::write_bottomViewExposureTime(Tango::WAttribute &attr)
{
	DEBUG_STREAM << "Hamamatsu::write_bottomViewExposureTime(Tango::WAttribute &attr) entering... "<< endl;

	try
	{
        attr.get_write_value(attr_bottomViewExposureTime_write);
        m_camera->setViewExpTime2((double) (attr_bottomViewExposureTime_write / 1000.0));

        m_BottomViewExposureTime = (double)attr_bottomViewExposureTime_write;
		PropertyHelper::set_property(this, "MemorizedBottomViewExposureTime", m_BottomViewExposureTime);
	}
	catch(Tango::DevFailed& df)
	{
		ERROR_STREAM << df << endl;
		//- rethrow exception
		Tango::Except::re_throw_exception(df,
                                          "TANGO_DEVICE_ERROR",
                                          string(df.errors[0].desc).c_str(),
                                          "Hamamatsu::write_bottomViewExposureTime");
	}
	catch(Exception& e)
	{
		ERROR_STREAM << e.getErrMsg() << endl;
		//- throw exception
        Tango::Except::throw_exception("TANGO_DEVICE_ERROR",
                                       e.getErrMsg().c_str(),
                                       "Hamamatsu::write_bottomViewExposureTime");
	}	
}

//+----------------------------------------------------------------------------
//
// method : 		Hamamatsu::read_wViewEnabled
// 
// description : 	Extract real attribute values for wViewEnabled acquisition result.
//
//-----------------------------------------------------------------------------
void Hamamatsu::read_wViewEnabled(Tango::Attribute &attr)
{
	DEBUG_STREAM << "Hamamatsu::read_wViewEnabled(Tango::Attribute &attr) entering... "<< endl;

	try
	{
		bool enabled = false;
		
        m_camera->getViewMode(enabled);
		*attr_wViewEnabled_read = enabled;
		attr.set_value(attr_wViewEnabled_read);
	}
	catch(Tango::DevFailed& df)
	{
		ERROR_STREAM << df << endl;
		//- rethrow exception
		Tango::Except::re_throw_exception(df,
                                          "TANGO_DEVICE_ERROR",
                                          string(df.errors[0].desc).c_str(),
                                          "Hamamatsu::read_wViewEnabled");
	}
	catch(Exception& e)
	{
		ERROR_STREAM << e.getErrMsg() << endl;
		//- throw exception
        Tango::Except::throw_exception("TANGO_DEVICE_ERROR",
                                       e.getErrMsg().c_str(),
                                       "Hamamatsu::read_wViewEnabled");
	}
}

//+----------------------------------------------------------------------------
//
// method : 		Hamamatsu::write_wViewEnabled
// 
// description : 	Write wViewEnabled attribute values to hardware.
//
//-----------------------------------------------------------------------------
void Hamamatsu::write_wViewEnabled(Tango::WAttribute &attr)
{
	DEBUG_STREAM << "Hamamatsu::write_wViewEnabled(Tango::WAttribute &attr) entering... "<< endl;

	try
	{
        attr.get_write_value(attr_wViewEnabled_write);

        // We want to activate W-VIEW mode
        if(attr_wViewEnabled_write)
        {
            // checking if we are in full frame ROI, the only ROI which is allowed.
            Size FullSize;
            m_camera->getDetectorMaxImageSize(FullSize);

            Roi CurrentROI;
            Bin CurrentBin;

            m_ct->image()->getRoi(CurrentROI);
            m_ct->image()->getBin(CurrentBin);
            Roi FullROI(Point(0, 0), Size(FullSize.getWidth() / CurrentBin.getX(), FullSize.getHeight() / CurrentBin.getY()));

            if(CurrentROI != FullROI)
            {
                stringstream ErrorTxt;

                ErrorTxt << "W-VIEW mode does not support the current ROI (";
                ErrorTxt << CurrentROI.getTopLeft().x        << ", ";
                ErrorTxt << CurrentROI.getTopLeft().y        << ", ";
                ErrorTxt << CurrentROI.getSize().getWidth()  << ", ";
                ErrorTxt << CurrentROI.getSize().getHeight() << ").\n\n";

                ErrorTxt << "Please define a full frame ROI\n";
                ErrorTxt << "using ResetROI or SetROI (";
                ErrorTxt << FullROI.getTopLeft().x        << ", ";
                ErrorTxt << FullROI.getTopLeft().y        << ", ";
                ErrorTxt << FullROI.getSize().getWidth()  << ", ";
                ErrorTxt << FullROI.getSize().getHeight() << ") commands.";

                Tango::Except::throw_exception("TANGO_DEVICE_ERROR",
                                               ErrorTxt.str().c_str(),
                                               "Hamamatsu::write_wViewEnabled");
            }
        }

        m_camera->setViewMode(attr_wViewEnabled_write);
        m_wViewEnabled = attr_wViewEnabled_write;
		PropertyHelper::set_property(this, "MemorizedWViewEnabled", m_wViewEnabled);

        if(m_wViewEnabled)
        {
            // reseting the views exposures
            {
                m_camera->setViewExpTime1(m_TopViewExposureTime    / 1000.0);
                m_camera->setViewExpTime2(m_BottomViewExposureTime / 1000.0); 
            }
        }
	}
	catch(Tango::DevFailed& df)
	{
		ERROR_STREAM << df << endl;
		//- rethrow exception
		Tango::Except::re_throw_exception(df,
                                          "TANGO_DEVICE_ERROR",
                                          string(df.errors[0].desc).c_str(),
                                          "Hamamatsu::write_wViewEnabled");
	}
	catch(Exception& e)
	{
		ERROR_STREAM << e.getErrMsg() << endl;
		//- throw exception
        Tango::Except::throw_exception("TANGO_DEVICE_ERROR",
                                       e.getErrMsg().c_str(),
                                       "Hamamatsu::write_wViewEnabled");
	}	
}

//+----------------------------------------------------------------------------
//
// method : 		Hamamatsu::read_fps
// 
// description : 	Extract real attribute values for fps acquisition result.
//
//-----------------------------------------------------------------------------
void Hamamatsu::read_fps(Tango::Attribute &attr)
{
	DEBUG_STREAM << "Hamamatsu::read_fps(Tango::Attribute &attr) entering... "<< endl;

	try
	{
		double fps = 0.0;
		m_camera->getFPS(fps);
		*attr_fps_read = fps;
		attr.set_value(attr_fps_read);
	}
	catch(Tango::DevFailed& df)
	{
		ERROR_STREAM << df << endl;
		//- rethrow exception
		Tango::Except::re_throw_exception(df,
                                          "TANGO_DEVICE_ERROR",
                                          string(df.errors[0].desc).c_str(),
                                          "Hamamatsu::read_fps");
	}
	catch(Exception& e)
	{
		ERROR_STREAM << e.getErrMsg() << endl;
		//- throw exception
        Tango::Except::throw_exception("TANGO_DEVICE_ERROR",
                                       e.getErrMsg().c_str(),
                                       "Hamamatsu::read_fps");
	}
}

//+----------------------------------------------------------------------------
//
// method : 		Hamamatsu::read_lostFrames
// 
// description : 	Extract real attribute values for lostFrames acquisition result.
//
//-----------------------------------------------------------------------------
void Hamamatsu::read_lostFrames(Tango::Attribute &attr)
{
	DEBUG_STREAM << "Hamamatsu::read_lostFrames(Tango::Attribute &attr) entering... "<< endl;
	
	try
	{
		unsigned long int lostFrames = 0;
		m_camera->getLostFrames(lostFrames);
		*attr_lostFrames_read = lostFrames;
		attr.set_value(attr_lostFrames_read);
	}
	catch(Tango::DevFailed& df)
	{
		ERROR_STREAM << df << endl;
		//- rethrow exception
		Tango::Except::re_throw_exception(df,
                                          "TANGO_DEVICE_ERROR",
                                          string(df.errors[0].desc).c_str(),
                                          "Hamamatsu::read_lostFrames");
	}
	catch(Exception& e)
	{
		ERROR_STREAM << e.getErrMsg() << endl;
		//- throw exception
        Tango::Except::throw_exception("TANGO_DEVICE_ERROR",
                                       e.getErrMsg().c_str(),
                                       "Hamamatsu::read_lostFrames");
	}	
}


//+----------------------------------------------------------------------------
//
// method : 		Hamamatsu::read_readoutSpeed
//
// description : 	Extract real attribute values for readoutSpeed acquisition result.
//
//-----------------------------------------------------------------------------
void Hamamatsu::read_readoutSpeed(Tango::Attribute &attr)
{
	DEBUG_STREAM << "Hamamatsu::read_readoutSpeed(Tango::Attribute &attr) entering... "<< endl;

	try
	{
		short int readoutSpeed = 0;
		m_camera->getReadoutSpeed(readoutSpeed);

		std::string readoutSpeedName = "";
		switch (readoutSpeed)
		{
            case READOUTSPEED_SLOW_VALUE:	readoutSpeedName = READOUTSPEED_SLOW_NAME;
				break;
            case READOUTSPEED_NORMAL_VALUE:	readoutSpeedName = READOUTSPEED_NORMAL_NAME;
				break;
			default:	readoutSpeedName = "ERROR";
				break;
		}

		strcpy(*attr_readoutSpeed_read, readoutSpeedName.c_str());
		attr.set_value(attr_readoutSpeed_read);
	}
	catch(Tango::DevFailed& df)
	{
		ERROR_STREAM << df << endl;
		//- rethrow exception
		Tango::Except::re_throw_exception(df,
                                          "TANGO_DEVICE_ERROR",
                                          string(df.errors[0].desc).c_str(),
                                          "Hamamatsu::read_readoutSpeed");
	}
	catch(Exception& e)
	{
		ERROR_STREAM << e.getErrMsg() << endl;
		//- throw exception
        Tango::Except::throw_exception("TANGO_DEVICE_ERROR",
                                       e.getErrMsg().c_str(),
                                       "Hamamatsu::read_readoutSpeed");
	}	
}

//+----------------------------------------------------------------------------
//
// method : 		Hamamatsu::write_readoutSpeed
//
// description : 	Write readoutSpeed attribute values to hardware.
//
//-----------------------------------------------------------------------------
void Hamamatsu::write_readoutSpeed(Tango::WAttribute &attr)
{
	DEBUG_STREAM << "Hamamatsu::write_readoutSpeed(Tango::WAttribute &attr) entering... "<< endl;
	
	try
	{
		m_readoutSpeed = *attr_readoutSpeed_read;
		attr.get_write_value(attr_readoutSpeed_write);
		string current = attr_readoutSpeed_write;
		transform(current.begin(), current.end(), current.begin(), ::toupper);
        if (current != READOUTSPEED_NORMAL_NAME &&
            current != READOUTSPEED_SLOW_NAME)
		{			
            attr_readoutSpeed_write = const_cast<Tango::DevString>(m_readoutSpeed.c_str());
			string userMsg;
            userMsg = string("Available Readout speeds are:\n- ") + string(READOUTSPEED_NORMAL_NAME) + string("\n- ") + string(READOUTSPEED_SLOW_NAME);

            Tango::Except::throw_exception(	"CONFIGURATION_ERROR",
                                            userMsg.c_str(),
                                            "Hamamatsu::write_readoutSpeed");
		}

        short int readoutSpeed = READOUTSPEED_NORMAL_VALUE;
        if (current == READOUTSPEED_SLOW_NAME)
            readoutSpeed = READOUTSPEED_SLOW_VALUE;
        else if (current == READOUTSPEED_NORMAL_NAME)
            readoutSpeed = READOUTSPEED_NORMAL_VALUE;
		
		//- THIS IS AN AVAILABLE READOUT SPEED
		m_readoutSpeed = current;
		m_camera->setReadoutSpeed(readoutSpeed);
		PropertyHelper::set_property(this, "MemorizedReadoutSpeed", m_readoutSpeed);
	}
	catch(Tango::DevFailed& df)
	{
		ERROR_STREAM << df << endl;
		//- rethrow exception
		Tango::Except::re_throw_exception(df,
                                          "TANGO_DEVICE_ERROR",
                                          string(df.errors[0].desc).c_str(),
                                          "Hamamatsu::write_readoutSpeed");
	}
	catch(Exception& e)
	{
		ERROR_STREAM << e.getErrMsg() << endl;
		//- throw exception
        Tango::Except::throw_exception("TANGO_DEVICE_ERROR",
                                       e.getErrMsg().c_str(),
                                       "Hamamatsu::write_readoutSpeed");
	}	
}

//+------------------------------------------------------------------
/**
 *	method:	Hamamatsu::dev_state
 *
 *	description:	method to execute "State"
 *	This command gets the device state (stored in its <i>device_state</i> data member) and returns it to the caller.
 *
 * @return	State Code
 *
 */
//+------------------------------------------------------------------
Tango::DevState Hamamatsu::dev_state()
{
	Tango::DevState	argout = DeviceImpl::dev_state();
	DEBUG_STREAM << "Hamamatsu::dev_state(): entering... !" << endl;

	//	Add your own code to control device here
	stringstream    DeviceStatus;
	DeviceStatus     << "";
	Tango::DevState DeviceState    = Tango::STANDBY;
	if(!m_is_device_initialized )
	{
		DeviceState            = Tango::FAULT;
		DeviceStatus        << m_status_message.str();
	}
	else
	{
		// state & status are retrieved from Factory, Factory is updated by Generic device
		DeviceState = ControlFactory::instance().get_state();
		DeviceStatus << ControlFactory::instance().get_status();
	}

	set_state(DeviceState);
	set_status(DeviceStatus.str());

	return DeviceState;
}



}	//	namespace
