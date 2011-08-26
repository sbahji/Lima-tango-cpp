static const char *RcsId = "$Id:  $";
//+=============================================================================
//
// file :         PilatusPixelDetector.cpp
//
// description :  C++ source for the PilatusPixelDetector and its commands.
//                The class is derived from Device. It represents the
//                CORBA servant object which will be accessed from the
//                network. All commands which can be executed on the
//                PilatusPixelDetector are implemented in this file.
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
//          This file is generated by POGO
//    (Program Obviously used to Generate tango Object)
//
//         (c) - Software Engineering Group - ESRF
//=============================================================================



//===================================================================
//
//	The following table gives the correspondence
//	between commands and method name.
//
//  Command name         |  Method name
//	----------------------------------------
//  State                |  dev_state()
//  Status               |  dev_status()
//  SetThresholdAndGain  |  set_threshold_and_gain()
//  SetMxSettings        |  set_mx_settings()
//  SendAnyCommand       |  send_any_command()
//
//===================================================================



#include <PilatusPixelDetector.h>
#include <PilatusPixelDetectorClass.h>
#include <tango.h>
#include <PogoHelper.h>

namespace PilatusPixelDetector_ns
{

//+----------------------------------------------------------------------------
//
// method :         PilatusPixelDetector::PilatusPixelDetector(string &s)
//
// description :     constructor for simulated PilatusPixelDetector
//
// in : - cl : Pointer to the DeviceClass object
//      - s : Device name
//
//-----------------------------------------------------------------------------
PilatusPixelDetector::PilatusPixelDetector(Tango::DeviceClass *cl,string &s)
:Tango::Device_4Impl(cl,s.c_str())
{
    init_device();
}

PilatusPixelDetector::PilatusPixelDetector(Tango::DeviceClass *cl,const char *s)
:Tango::Device_4Impl(cl,s)
{
    init_device();
}

PilatusPixelDetector::PilatusPixelDetector(Tango::DeviceClass *cl,const char *s,const char *d)
:Tango::Device_4Impl(cl,s,d)
{
    init_device();
}
//+----------------------------------------------------------------------------
//
// method :         PilatusPixelDetector::delete_device()
//
// description :     will be called at device destruction or at init command.
//
//-----------------------------------------------------------------------------
void PilatusPixelDetector::delete_device()
{
    INFO_STREAM << "PilatusPixelDetector::PilatusPixelDetector() delete device " << device_name << endl;    
    //    Delete device allocated objects
    DELETE_SCALAR_ATTRIBUTE(attr_latency_read);
    DELETE_SCALAR_ATTRIBUTE(attr_threshold_read);
    DELETE_DEVSTRING_ATTRIBUTE(attr_gain_read);
    DELETE_DEVSTRING_ATTRIBUTE(attr_imagePath_read);
    DELETE_DEVSTRING_ATTRIBUTE(attr_fileName_read);       

    //!!!! ONLY LimaDetector device can do this !!!!
    //if(m_ct!=0)
    //{
    //    ControlFactory::instance().reset("PilatusPixelDetector");
    //    m_ct = 0;
    //}
}

//+----------------------------------------------------------------------------
//
// method :         PilatusPixelDetector::init_device()
//
// description :     will be called at device initialization.
//
//-----------------------------------------------------------------------------
void PilatusPixelDetector::init_device()
{
    INFO_STREAM << "PilatusPixelDetector::PilatusPixelDetector() create device " << device_name << endl;

    // Initialise variables to default values
    //--------------------------------------------
	get_device_property();
    CREATE_SCALAR_ATTRIBUTE(attr_latency_read, 3.0);
    CREATE_SCALAR_ATTRIBUTE(attr_threshold_read);
    CREATE_DEVSTRING_ATTRIBUTE(attr_gain_read,MAX_ATTRIBUTE_STRING_LENGTH);
    CREATE_DEVSTRING_ATTRIBUTE(attr_imagePath_read,MAX_ATTRIBUTE_STRING_LENGTH);
    CREATE_DEVSTRING_ATTRIBUTE(attr_fileName_read,MAX_ATTRIBUTE_STRING_LENGTH);    

    m_is_device_initialized = false;
    m_status_message.str("");

    try
    {
        //- get the main object used to pilot the lima framework
        //in fact LimaDetector is create the singleton control objet
        //so this call, will only return existing object, no need to give it the ip !!
        m_ct = ControlFactory::instance().get_control("PilatusPixelDetector");
        
        //- get interface to specific camera
        m_hw = dynamic_cast<PilatusCpp::Interface*>(m_ct->hwInterface());
        if(m_hw==0)
        {
            INFO_STREAM<<"Initialization Failed : Unable to get the interface of camera plugin "<<"("<<"PilatusPixelDetector"<<") !"<< endl;
            m_status_message <<"Initialization Failed : Unable to get the interface of camera plugin "<<"("<<"PilatusPixelDetector"<<") !"<< endl;
            m_is_device_initialized = false;
            set_state(Tango::INIT);
            return;
        }

    }
    catch(Exception& e)
    {
        INFO_STREAM<<"Initialization Failed : "<<e.getErrMsg()<<endl;
        m_status_message <<"Initialization Failed : "<<e.getErrMsg( )<< endl;
        m_is_device_initialized = false;
        set_state(Tango::INIT);
        return;
    }
    catch(...)
    {
        INFO_STREAM<<"Initialization Failed : UNKNOWN"<<endl;
        m_status_message <<"Initialization Failed : UNKNOWN"<< endl;
        set_state(Tango::INIT);
        m_is_device_initialized = false;
        return;
    }
    m_is_device_initialized = true;
    set_state(Tango::STANDBY);
    this->dev_state();
}


//+----------------------------------------------------------------------------
//
// method : 		PilatusPixelDetector::get_device_property()
// 
// description : 	Read the device properties from database.
//
//-----------------------------------------------------------------------------
void PilatusPixelDetector::get_device_property()
{
	//	Initialize your default values here (if not done with  POGO).
	//------------------------------------------------------------------

	//	Read device properties from database.(Automatic code generation)
	//------------------------------------------------------------------
	Tango::DbData	dev_prop;
	dev_prop.push_back(Tango::DbDatum("DetectorPort"));
	dev_prop.push_back(Tango::DbDatum("DetectorIP"));

	//	Call database and extract values
	//--------------------------------------------
	if (Tango::Util::instance()->_UseDb==true)
		get_db_device()->get_property(dev_prop);
	Tango::DbDatum	def_prop, cl_prop;
	PilatusPixelDetectorClass	*ds_class =
		(static_cast<PilatusPixelDetectorClass *>(get_device_class()));
	int	i = -1;

	//	Try to initialize DetectorPort from class property
	cl_prop = ds_class->get_class_property(dev_prop[++i].name);
	if (cl_prop.is_empty()==false)	cl_prop  >>  detectorPort;
	else {
		//	Try to initialize DetectorPort from default device value
		def_prop = ds_class->get_default_device_property(dev_prop[i].name);
		if (def_prop.is_empty()==false)	def_prop  >>  detectorPort;
	}
	//	And try to extract DetectorPort value from database
	if (dev_prop[i].is_empty()==false)	dev_prop[i]  >>  detectorPort;

	//	Try to initialize DetectorIP from class property
	cl_prop = ds_class->get_class_property(dev_prop[++i].name);
	if (cl_prop.is_empty()==false)	cl_prop  >>  detectorIP;
	else {
		//	Try to initialize DetectorIP from default device value
		def_prop = ds_class->get_default_device_property(dev_prop[i].name);
		if (def_prop.is_empty()==false)	def_prop  >>  detectorIP;
	}
	//	And try to extract DetectorIP value from database
	if (dev_prop[i].is_empty()==false)	dev_prop[i]  >>  detectorIP;



	//	End of Automatic code generation
	//------------------------------------------------------------------
    create_property_if_empty(dev_prop,"127.0.0.1","DetectorIP");
    create_property_if_empty(dev_prop,"-1","DetectorPort");
}
//+----------------------------------------------------------------------------
//
// method :         PilatusPixelDetector::always_executed_hook()
//
// description :     method always executed before any command is executed
//
//-----------------------------------------------------------------------------
void PilatusPixelDetector::always_executed_hook()
{

}
//+----------------------------------------------------------------------------
//
// method :         PilatusPixelDetector::read_attr_hardware
//
// description :     Hardware acquisition for attributes.
//
//-----------------------------------------------------------------------------
void PilatusPixelDetector::read_attr_hardware(vector<long> &attr_list)
{
    DEBUG_STREAM << "PilatusPixelDetector::read_attr_hardware(vector<long> &attr_list) entering... "<< endl;
    //    Add your own code here
}
//+----------------------------------------------------------------------------
//
// method : 		PilatusPixelDetector::read_latency
// 
// description : 	Extract real attribute values for latency acquisition result.
//
//-----------------------------------------------------------------------------
void PilatusPixelDetector::read_latency(Tango::Attribute &attr)
{
	DEBUG_STREAM << "PilatusPixelDetector::read_latency(Tango::Attribute &attr) entering... "<< endl;
    try
    {
        double latency = 0.003;
        m_ct->acquisition()->getLatencyTime(latency);
        *attr_latency_read = (Tango::DevDouble)(latency*1000.0);//latency USER OUTPUT is in millisec
        attr.set_value(attr_latency_read);
    }
    catch(Tango::DevFailed& df)
    {
        ERROR_STREAM << df << endl;
        //- rethrow exception
        Tango::Except::re_throw_exception(df,
                     static_cast<const char*> ("TANGO_DEVICE_ERROR"),
                     static_cast<const char*> (string(df.errors[0].desc).c_str()),
                     static_cast<const char*> ("PilatusPixelDetector::read_latency"));
    }
    catch(Exception& e)
    {
        ERROR_STREAM << e.getErrMsg() << endl;
        //- throw exception
        Tango::Except::throw_exception(
                     static_cast<const char*> ("TANGO_DEVICE_ERROR"),
                     static_cast<const char*> (e.getErrMsg().c_str()),
                     static_cast<const char*> ("PilatusPixelDetector::read_latency"));
    }
}

//+----------------------------------------------------------------------------
//
// method : 		PilatusPixelDetector::write_latency
// 
// description : 	Write latency attribute values to hardware.
//
//-----------------------------------------------------------------------------
void PilatusPixelDetector::write_latency(Tango::WAttribute &attr)
{
	DEBUG_STREAM << "PilatusPixelDetector::write_latency(Tango::WAttribute &attr) entering... "<< endl;
    try
    {
        attr.get_write_value(attr_latency_write);
        m_ct->acquisition()->setLatencyTime((double)(attr_latency_write/1000.0));//latency USER INPUT is in millisec
    }
    catch(Tango::DevFailed& df)
    {
        ERROR_STREAM << df << endl;
        //- rethrow exception
        Tango::Except::re_throw_exception(df,
                     static_cast<const char*> ("TANGO_DEVICE_ERROR"),
                     static_cast<const char*> (string(df.errors[0].desc).c_str()),
                     static_cast<const char*> ("PilatusPixelDetector::write_latency"));
    }
    catch(Exception& e)
    {
        ERROR_STREAM << e.getErrMsg() << endl;
        //- throw exception
        Tango::Except::throw_exception(
                     static_cast<const char*> ("TANGO_DEVICE_ERROR"),
                     static_cast<const char*> (e.getErrMsg().c_str()),
                     static_cast<const char*> ("PilatusPixelDetector::write_latency"));
    }
}

//+----------------------------------------------------------------------------
//
// method : 		PilatusPixelDetector::read_imagePath
// 
// description : 	Extract real attribute values for imagePath acquisition result.
//
//-----------------------------------------------------------------------------
void PilatusPixelDetector::read_imagePath(Tango::Attribute &attr)
{
	DEBUG_STREAM << "PilatusPixelDetector::read_imagePath(Tango::Attribute &attr) entering... "<< endl;
    try
    {
        strcpy(*attr_imagePath_read, m_hw->getImagePath().c_str());
        attr.set_value(attr_imagePath_read);
    }
    catch(Tango::DevFailed& df)
    {
        ERROR_STREAM << df << endl;
        //- rethrow exception
        Tango::Except::re_throw_exception(df,
                     static_cast<const char*> ("TANGO_DEVICE_ERROR"),
                     static_cast<const char*> (string(df.errors[0].desc).c_str()),
                     static_cast<const char*> ("PilatusPixelDetector::read_imagePath"));
    }
    catch(Exception& e)
    {
        ERROR_STREAM << e.getErrMsg() << endl;
        //- throw exception
        Tango::Except::throw_exception(
                     static_cast<const char*> ("TANGO_DEVICE_ERROR"),
                     static_cast<const char*> (e.getErrMsg().c_str()),
                     static_cast<const char*> ("PilatusPixelDetector::read_imagePath"));
    }    
}

//+----------------------------------------------------------------------------
//
// method : 		PilatusPixelDetector::write_imagePath
// 
// description : 	Write imagePath attribute values to hardware.
//
//-----------------------------------------------------------------------------
void PilatusPixelDetector::write_imagePath(Tango::WAttribute &attr)
{
	DEBUG_STREAM << "PilatusPixelDetector::write_imagePath(Tango::WAttribute &attr) entering... "<< endl;
    try
    {
        attr.get_write_value(attr_imagePath_write);
        m_hw->setImagePath(attr_imagePath_write);
    }
    catch(Tango::DevFailed& df)
    {
        ERROR_STREAM << df << endl;
        //- rethrow exception
        Tango::Except::re_throw_exception(df,
                     static_cast<const char*> ("TANGO_DEVICE_ERROR"),
                     static_cast<const char*> (string(df.errors[0].desc).c_str()),
                     static_cast<const char*> ("PilatusPixelDetector::write_imagePath"));
    }
    catch(Exception& e)
    {
        ERROR_STREAM << e.getErrMsg() << endl;
        //- throw exception
        Tango::Except::throw_exception(
                     static_cast<const char*> ("TANGO_DEVICE_ERROR"),
                     static_cast<const char*> (e.getErrMsg().c_str()),
                     static_cast<const char*> ("PilatusPixelDetector::write_imagePath"));
    }    
}

//+----------------------------------------------------------------------------
//
// method : 		PilatusPixelDetector::read_fileName
// 
// description : 	Extract real attribute values for fileName acquisition result.
//
//-----------------------------------------------------------------------------
void PilatusPixelDetector::read_fileName(Tango::Attribute &attr)
{
	DEBUG_STREAM << "PilatusPixelDetector::read_fileName(Tango::Attribute &attr) entering... "<< endl;
    try
    {
        strcpy(*attr_fileName_read, m_hw->getFileName().c_str());
        attr.set_value(attr_fileName_read);
    }
    catch(Tango::DevFailed& df)
    {
        ERROR_STREAM << df << endl;
        //- rethrow exception
        Tango::Except::re_throw_exception(df,
                     static_cast<const char*> ("TANGO_DEVICE_ERROR"),
                     static_cast<const char*> (string(df.errors[0].desc).c_str()),
                     static_cast<const char*> ("PilatusPixelDetector::read_fileName"));
    }
    catch(Exception& e)
    {
        ERROR_STREAM << e.getErrMsg() << endl;
        //- throw exception
        Tango::Except::throw_exception(
                     static_cast<const char*> ("TANGO_DEVICE_ERROR"),
                     static_cast<const char*> (e.getErrMsg().c_str()),
                     static_cast<const char*> ("PilatusPixelDetector::read_fileName"));
    }        
}

//+----------------------------------------------------------------------------
//
// method : 		PilatusPixelDetector::write_fileName
// 
// description : 	Write fileName attribute values to hardware.
//
//-----------------------------------------------------------------------------
void PilatusPixelDetector::write_fileName(Tango::WAttribute &attr)
{
	DEBUG_STREAM << "PilatusPixelDetector::write_fileName(Tango::WAttribute &attr) entering... "<< endl;
    try
    {
        attr.get_write_value(attr_fileName_write);
        m_hw->setFileName(attr_fileName_write);
    }
    catch(Tango::DevFailed& df)
    {
        ERROR_STREAM << df << endl;
        //- rethrow exception
        Tango::Except::re_throw_exception(df,
                     static_cast<const char*> ("TANGO_DEVICE_ERROR"),
                     static_cast<const char*> (string(df.errors[0].desc).c_str()),
                     static_cast<const char*> ("PilatusPixelDetector::write_fileName"));
    }
    catch(Exception& e)
    {
        ERROR_STREAM << e.getErrMsg() << endl;
        //- throw exception
        Tango::Except::throw_exception(
                     static_cast<const char*> ("TANGO_DEVICE_ERROR"),
                     static_cast<const char*> (e.getErrMsg().c_str()),
                     static_cast<const char*> ("PilatusPixelDetector::write_fileName"));
    }       
}

//+----------------------------------------------------------------------------
//
// method :         PilatusPixelDetector::write_threshold
//
// description :     Write threshold attribute values to hardware.
//
//-----------------------------------------------------------------------------
void PilatusPixelDetector::write_threshold(Tango::WAttribute &attr)
{
    DEBUG_STREAM << "PilatusPixelDetector::write_threshold(Tango::WAttribute &attr) entering... "<< endl;
    try
    {
        attr.get_write_value(attr_threshold_write);
        m_hw->setThresholdGain(attr_threshold_write, m_hw->getGain());
    }
    catch(Tango::DevFailed& df)
    {
        ERROR_STREAM << df << endl;
        //- rethrow exception
        Tango::Except::re_throw_exception(df,
                     static_cast<const char*> ("TANGO_DEVICE_ERROR"),
                     static_cast<const char*> (string(df.errors[0].desc).c_str()),
                     static_cast<const char*> ("PilatusPixelDetector::write_threshold"));
    }
    catch(Exception& e)
    {
        ERROR_STREAM << e.getErrMsg() << endl;
        //- throw exception
        Tango::Except::throw_exception(
                     static_cast<const char*> ("TANGO_DEVICE_ERROR"),
                     static_cast<const char*> (e.getErrMsg().c_str()),
                     static_cast<const char*> ("PilatusPixelDetector::write_threshold"));
    }
}


//+----------------------------------------------------------------------------
//
// method :         PilatusPixelDetector::read_threshold
//
// description :     Extract real attribute values for threshold acquisition result.
//
//-----------------------------------------------------------------------------
void PilatusPixelDetector::read_threshold(Tango::Attribute &attr)
{
    DEBUG_STREAM << "PilatusPixelDetector::read_threshold(Tango::Attribute &attr) entering... "<< endl;
    try
    {
        *attr_threshold_read = m_hw->getThreshold();
        attr.set_value(attr_threshold_read);
    }
    catch(Tango::DevFailed& df)
    {
        ERROR_STREAM << df << endl;
        //- rethrow exception
        Tango::Except::re_throw_exception(df,
                     static_cast<const char*> ("TANGO_DEVICE_ERROR"),
                     static_cast<const char*> (string(df.errors[0].desc).c_str()),
                     static_cast<const char*> ("PilatusPixelDetector::read_threshold"));
    }
    catch(Exception& e)
    {
        ERROR_STREAM << e.getErrMsg() << endl;
        //- throw exception
        Tango::Except::throw_exception(
                     static_cast<const char*> ("TANGO_DEVICE_ERROR"),
                     static_cast<const char*> (e.getErrMsg().c_str()),
                     static_cast<const char*> ("PilatusPixelDetector::read_threshold"));
    }
}

//+----------------------------------------------------------------------------
//
// method :         PilatusPixelDetector::write_gain
//
// description :     Write gain attribute values to hardware.
//
//-----------------------------------------------------------------------------
void PilatusPixelDetector::write_gain(Tango::WAttribute &attr)
{
    DEBUG_STREAM << "PilatusPixelDetector::write_gain(Tango::WAttribute &attr) entering... "<< endl;
    try
    {
        m_gain = *attr_gain_read;
        string previous = m_gain;
        attr.get_write_value(attr_gain_write);
        string current = attr_gain_write;
        if(current.compare("LOW")!=0 && current.compare("MID")!=0 && current.compare("HIGH")!=0 && current.compare("UHIGH")!=0)
        {
            m_gain = previous;
            attr_gain_write = new char [m_gain.size()+1];
            strcpy (attr_gain_write, m_gain.c_str());

            Tango::Except::throw_exception(
                         (const char*) ("CONFIGURATION_ERROR"),
                         (const char*) ("Available Gain values are: \n- LOW \n- MID \n- HIGH \n- UHIGH"),
                         (const char*) ("PilatusPixelDetector::write_gain"));
        }

        //- THIS IS AN AVAILABLE TRIGER MODE
        m_gain = attr_gain_write;

        Communication::Gain new_gain;
        if(m_gain.compare("LOW")==0)
            new_gain = Communication::LOW;
        else if(m_gain.compare("MID")==0)
            new_gain = Communication::MID;
        else if(m_gain.compare("HIGH")==0)
            new_gain = Communication::HIGH;
        else
            new_gain = Communication::UHIGH;

        m_hw->setThresholdGain(m_hw->getThreshold(), new_gain);
    }
    catch(Tango::DevFailed& df)
    {
        ERROR_STREAM << df << endl;
        //- rethrow exception
        Tango::Except::re_throw_exception(df,
                     static_cast<const char*> ("TANGO_DEVICE_ERROR"),
                     static_cast<const char*> (string(df.errors[0].desc).c_str()),
                     static_cast<const char*> ("PilatusPixelDetector::write_gain"));
    }
    catch(Exception& e)
    {
        ERROR_STREAM << e.getErrMsg() << endl;
        //- throw exception
        Tango::Except::throw_exception(
                     static_cast<const char*> ("TANGO_DEVICE_ERROR"),
                     static_cast<const char*> (e.getErrMsg().c_str()),
                     static_cast<const char*> ("PilatusPixelDetector::write_gain"));
    }
}

//+----------------------------------------------------------------------------
//
// method :         PilatusPixelDetector::read_gain
//
// description :     Extract real attribute values for gain acquisition result.
//
//-----------------------------------------------------------------------------
void PilatusPixelDetector::read_gain(Tango::Attribute &attr)
{
    DEBUG_STREAM << "PilatusPixelDetector::read_gain(Tango::Attribute &attr) entering... "<< endl;
    try
    {
        Communication::Gain current_gain = m_hw->getGain();
        switch (current_gain)
        {
            case Communication::LOW     : strcpy(*attr_gain_read, "LOW")    ;    break;
            case Communication::MID     : strcpy(*attr_gain_read, "MID")    ;    break;
            case Communication::HIGH    : strcpy(*attr_gain_read, "HIGH")    ;    break;
            default /*UHIGH*/           : strcpy(*attr_gain_read, "UHIGH")    ;    break;
        }

        attr.set_value(attr_gain_read);
    }
    catch(Tango::DevFailed& df)
    {
        ERROR_STREAM << df << endl;
        //- rethrow exception
        Tango::Except::re_throw_exception(df,
                     static_cast<const char*> ("TANGO_DEVICE_ERROR"),
                     static_cast<const char*> (string(df.errors[0].desc).c_str()),
                     static_cast<const char*> ("PilatusPixelDetector::read_gain"));
    }
    catch(Exception& e)
    {
        ERROR_STREAM << e.getErrMsg() << endl;
        //- throw exception
        Tango::Except::throw_exception(
                     static_cast<const char*> ("TANGO_DEVICE_ERROR"),
                     static_cast<const char*> (e.getErrMsg().c_str()),
                     static_cast<const char*> ("PilatusPixelDetector::read_gain"));
    }
}

//+------------------------------------------------------------------
/**
 *    method:    PilatusPixelDetector::dev_state
 *
 *    description:    method to execute "State"
 *    This command gets the device state (stored in its <i>device_state</i> data member) and returns it to the caller.
 *
 * @return    State Code
 *
 */
//+------------------------------------------------------------------
Tango::DevState PilatusPixelDetector::dev_state()
{
    Tango::DevState    argout = DeviceImpl::dev_state();
    DEBUG_STREAM << "PilatusPixelDetector::dev_state(): entering... !" << endl;
    //    Add your own code to control device here
    stringstream    DeviceStatus;
    DeviceStatus     << "";
    Tango::DevState DeviceState    = Tango::STANDBY;
    if(!m_is_device_initialized )
    {
        DeviceState            = Tango::INIT;
        DeviceStatus        << m_status_message.str();
    }
    else if (m_ct==0)
    {
        DeviceState            = Tango::INIT;
        DeviceStatus        <<"Initialization Failed : Unable to get the lima control object !\n\n";
    }
    else
    {
        CtControl::Status status;
        m_ct->getStatus(status);
        if (status.AcquisitionStatus == lima::AcqReady)
        {
                HwInterface::StatusType state;
                m_hw->getStatus(state); 

                if(state.acq == AcqRunning && state.det == DetExposure)
                {
                    DeviceState=Tango::RUNNING;
                    DeviceStatus<<"Acquisition is Running ...\n"<<endl;
                }
                else if(state.acq == AcqFault && state.det == DetFault)
                {                 
                    DeviceState=Tango::FAULT;//FAULT
                    DeviceStatus<<"Acquisition is in Fault\n"<<endl;
                }  
                else
                {
                    DeviceState=Tango::STANDBY;
                    DeviceStatus<<"Waiting for Request ...\n"<<endl;
                }
        }
        else if(status.AcquisitionStatus == lima::AcqRunning)
        {
            DeviceState=Tango::RUNNING;
            DeviceStatus<<"Acquisition is Running ...\n"<<endl;
        }
        else
        {
            DeviceState=Tango::FAULT;//FAULT
            DeviceStatus<<"Acquisition is in Fault\n"<<endl;
        }
    }

    set_state(DeviceState);
    set_status(DeviceStatus.str());

    argout = DeviceState;
    return argout;
}


//+------------------------------------------------------------------
/**
 *	method:	PilatusPixelDetector::set_threshold_and_gain
 *
 *	description:	method to execute "SetThresholdAndGain"
 *	Define Threshold (eV) and Gain (LOW, MID, HIGH, UHIGH).
 *
 * @param	argin	
 *
 */
//+------------------------------------------------------------------
void PilatusPixelDetector::set_threshold_and_gain(const Tango::DevVarLongStringArray *argin)
{
    DEBUG_STREAM << "PilatusPixelDetector::set_threshold_and_gain(): entering... !" << endl;

    //    Add your own code to control device here

    try
    {
        if(!argin->lvalue.length() || !argin->svalue.length())
        {
            //- throw exception
            Tango::Except::throw_exception(
                          (const char*) ("TANGO_DEVICE_ERROR"),
                          (const char*) ("Invalid number of parameters. Check input parameters (threshold, gain)\n"),
                          (const char*) ("PilatusPixelDetector::set_threshold_and_gain"));
        }


        Tango::DevLong input_threshold = argin->lvalue[0];

        std::string input_gain(argin->svalue[0].in());

        if(input_gain.compare("LOW")!=0 && input_gain.compare("MID")!=0 && input_gain.compare("HIGH")!=0 && input_gain.compare("UHIGH")!=0)
        {
            Tango::Except::throw_exception(
                         (const char*) ("TANGO_DEVICE_ERROR"),
                         (const char*) ("Available Gain values are: \n- LOW \n- MID \n- HIGH \n- UHIGH"),
                         (const char*) ("PilatusPixelDetector::set_threshold_and_gain"));
        }

        int new_threshold = input_threshold;

        Communication::Gain new_gain;
        if(input_gain.compare("LOW")==0)
            new_gain = Communication::LOW;
        else if(input_gain.compare("MID")==0)
            new_gain = Communication::MID;
        else if(input_gain.compare("HIGH")==0)
            new_gain = Communication::HIGH;
        else
            new_gain = Communication::UHIGH;

        m_hw->setThresholdGain(new_threshold, new_gain);
    }
    catch(Tango::DevFailed& df)
    {
        ERROR_STREAM << df << endl;
        //- rethrow exception
        Tango::Except::re_throw_exception(df,
                     static_cast<const char*> ("TANGO_DEVICE_ERROR"),
                     static_cast<const char*> (string(df.errors[0].desc).c_str()),
                     static_cast<const char*> ("PilatusPixelDetector::set_threshold_and_gain"));
    }
    catch(Exception& e)
    {
        ERROR_STREAM << e.getErrMsg() << endl;
        //- throw exception
        Tango::Except::throw_exception(
                     static_cast<const char*> ("TANGO_DEVICE_ERROR"),
                     static_cast<const char*> (e.getErrMsg().c_str()),
                     static_cast<const char*> ("PilatusPixelDetector::set_threshold_and_gain"));
    }
}

//+------------------------------------------------------------------
/**
 *	method:	PilatusPixelDetector::set_mx_settings
 *
 *	description:	method to execute "SetMxSettings"
 *	Set crystallographic parameters reported in the image header. <br>
 *	
 *	[parm_name value] [parm_name value] ... <br>
 *	
 *	Possible values :<br>
 *	Wavelength, Energy_range, Detector_distance, Detector_Voffset, Beam_xy, <br>
 *	Beam_x, Beam_y, Flux, Filter_transmission, Start_angle, Angle_increment, <br>
 *	Detector_2theta, Polarization, Alpha, Kappa, Phi, Phi_increment, Chi, <br>
 *	Chi_increment, Oscillation_axis, N_oscillations, Start_position, <br>
 *	Position_increment, Shutter_time, CBF_template_file <br>
 *
 * @param	argin	
 *
 */
//+------------------------------------------------------------------
void PilatusPixelDetector::set_mx_settings(Tango::DevString argin)
{
    DEBUG_STREAM << "PilatusPixelDetector::set_mx_settings(): entering... !" << endl;

    //    Add your own code to control device here
    try
    {
        std::string str_cmd_to_send = argin;
        INFO_STREAM<<"str_cmd_to_send = "<<str_cmd_to_send<<endl;
        m_hw->setMxSettings(str_cmd_to_send);
    }
    catch(Tango::DevFailed& df)
    {
        ERROR_STREAM << df << endl;
        //- rethrow exception
        Tango::Except::re_throw_exception(df,
                     static_cast<const char*> ("TANGO_DEVICE_ERROR"),
                     static_cast<const char*> (string(df.errors[0].desc).c_str()),
                     static_cast<const char*> ("PilatusPixelDetector::set_mx_settings"));
    }
    catch(Exception& e)
    {
        ERROR_STREAM << e.getErrMsg() << endl;
        //- throw exception
        Tango::Except::throw_exception(
                     static_cast<const char*> ("TANGO_DEVICE_ERROR"),
                     static_cast<const char*> (e.getErrMsg().c_str()),
                     static_cast<const char*> ("PilatusPixelDetector::set_mx_settings"));
    }

}


//+------------------------------------------------------------------
/**
 *	method:	PilatusPixelDetector::send_any_command
 *
 *	description:	method to execute "SendAnyCommand"
 *	Allow to send any commad to Camserver.<br>
 *	See documentation of Pilatus/Camserver.
 *
 * @param	argin	
 *
 */
//+------------------------------------------------------------------
void PilatusPixelDetector::send_any_command(Tango::DevString argin)
{
    DEBUG_STREAM << "PilatusPixelDetector::send_any_command(): entering... !" << endl;

    //    Add your own code to control device here
    try
    {
        std::string str_cmd_to_send = argin;
        INFO_STREAM<<"str_cmd_to_send = "<<str_cmd_to_send<<endl;
        m_hw->sendAnyCommand(str_cmd_to_send);
    }
    catch(Tango::DevFailed& df)
    {
        ERROR_STREAM << df << endl;
        //- rethrow exception
        Tango::Except::re_throw_exception(df,
                     static_cast<const char*> ("TANGO_DEVICE_ERROR"),
                     static_cast<const char*> (string(df.errors[0].desc).c_str()),
                     static_cast<const char*> ("PilatusPixelDetector::send_any_command"));
    }
    catch(Exception& e)
    {
        ERROR_STREAM << e.getErrMsg() << endl;

        //- throw exception
        Tango::Except::throw_exception(
                     static_cast<const char*> ("TANGO_DEVICE_ERROR"),
                     static_cast<const char*> (e.getErrMsg().c_str()),
                     static_cast<const char*> ("PilatusPixelDetector::send_any_command"));
    }
}

/*-------------------------------------------------------------------------
//       LimaDetector::store_value_as_property
/-------------------------------------------------------------------------*/
template <class T>
void PilatusPixelDetector::store_value_as_property (T value, string property_name)
{
    Tango::DbDatum current_value(property_name);
    current_value << value;
    Tango::DbData db_data;
    db_data.push_back(current_value);
    try
    {
        get_db_device()->put_property(db_data);
    }
    catch(Tango::DevFailed &df)
    {
        string message= "Error in storing " + property_name + " in Configuration DataBase ";
        LOG_ERROR((message));
        ERROR_STREAM<<df<<endl;
        //- rethrow exception
        Tango::Except::re_throw_exception(df,
                    static_cast<const char*> ("TANGO_DEVICE_ERROR"),
                    static_cast<const char*> (string(df.errors[0].desc).c_str()),
                    static_cast<const char*> ("LimaDetector::store_value_as_property"));
    }

}

/*-------------------------------------------------------------------------
//       LimaDetector::create_property_if_empty
/-------------------------------------------------------------------------*/
template <class T>
void PilatusPixelDetector::create_property_if_empty(Tango::DbData& dev_prop,T value,string property_name)
{
    int iPropertyIndex = FindIndexFromPropertyName(dev_prop,property_name);
    if (iPropertyIndex == -1) return;
    if (dev_prop[iPropertyIndex].is_empty())
    {
        Tango::DbDatum current_value(dev_prop[iPropertyIndex].name);
        current_value << value;
        Tango::DbData db_data;
        db_data.push_back(current_value);

        try
        {
            get_db_device()->put_property(db_data);
        }
        catch(Tango::DevFailed &df)
        {
            string message= "Error in storing " + property_name + " in Configuration DataBase ";
            LOG_ERROR((message));
            ERROR_STREAM<<df<<endl;
            //- rethrow exception
            Tango::Except::re_throw_exception(df,
                        static_cast<const char*> ("TANGO_DEVICE_ERROR"),
                        static_cast<const char*> (string(df.errors[0].desc).c_str()),
                        static_cast<const char*> ("LimaDetector::create_property_if_empty"));
        }
    }
}


/*-------------------------------------------------------------------------
//       LimaDetector::FindIndexFromPropertyName
/-------------------------------------------------------------------------*/
int PilatusPixelDetector::FindIndexFromPropertyName(Tango::DbData& dev_prop, string property_name)
{
    size_t iNbProperties = dev_prop.size();
    unsigned int i;
    for (i=0;i<iNbProperties;i++)
    {
        string sPropertyName(dev_prop[i].name);
        if (sPropertyName == property_name) return i;
    }
    if (i == iNbProperties) return -1;
    return i;
}



}	//	namespace
