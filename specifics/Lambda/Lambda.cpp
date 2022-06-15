/*----- PROTECTED REGION ID(Lambda.cpp) ENABLED START -----*/
static const char *RcsId = "$Id:  $";
//=============================================================================
//
// file :        Lambda.cpp
//
// description : C++ source for the Lambda class and its commands.
//               The class is derived from Device. It represents the
//               CORBA servant object which will be accessed from the
//               network. All commands which can be executed on the
//               Lambda are implemented in this file.
//
// project :     Sls dectector TANGO specific device.
//
// This file is part of Tango device class.
// 
// Tango is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// Tango is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with Tango.  If not, see <http://www.gnu.org/licenses/>.
// 
// $Author:  $
//
// $Revision:  $
// $Date:  $
//
// $HeadURL:  $
//
//=============================================================================
//                This file is generated by POGO
//        (Program Obviously used to Generate tango Object)
//=============================================================================


#include <Lambda.h>
#include <LambdaClass.h>
#include <helpers/PogoHelper.h>

namespace Lambda_ns
{
	//-------------------------------------------------------------------------
	// MAX SIZES FOR STRING ATTRIBUTES
	//-------------------------------------------------------------------------
	static const size_t STR_ATTR_SIZE_MAX = 255; // size max
}

/*----- PROTECTED REGION END -----*/	//	Lambda.cpp

/**
 *  Lambda class description:
 *    Device for Lambda detectors from XSpectrum.
 */

//================================================================
//  The following table gives the correspondence
//  between command and method names.
//
//  Command name  |  Method name
//================================================================
//  State         |  Inherited (no method)
//  Status        |  Inherited (no method)
//================================================================

//================================================================
//  Attributes managed are:
//================================================================
//  configFilesPath       |  Tango::DevString	Scalar
//  distortionCorrection  |  Tango::DevBoolean	Scalar
//  energyThreshold       |  Tango::DevDouble	Scalar
//  libraryVersion        |  Tango::DevString	Scalar
//  highVoltage           |  Tango::DevDouble	Scalar
//  humidity              |  Tango::DevDouble	Scalar
//  temperature           |  Tango::DevDouble	Scalar
//================================================================

namespace Lambda_ns
{
/*----- PROTECTED REGION ID(Lambda::namespace_starting) ENABLED START -----*/

//	static initializations

/*----- PROTECTED REGION END -----*/	//	Lambda::namespace_starting

//--------------------------------------------------------
/**
 *	Method      : Lambda::Lambda()
 *	Description : Constructors for a Tango device
 *                implementing the classLambda
 */
//--------------------------------------------------------
Lambda::Lambda(Tango::DeviceClass *cl, string &s)
 : TANGO_BASE_CLASS(cl, s.c_str())
{
	/*----- PROTECTED REGION ID(Lambda::constructor_1) ENABLED START -----*/
	init_device();
	/*----- PROTECTED REGION END -----*/	//	Lambda::constructor_1
}
//--------------------------------------------------------
Lambda::Lambda(Tango::DeviceClass *cl, const char *s)
 : TANGO_BASE_CLASS(cl, s)
{
	/*----- PROTECTED REGION ID(Lambda::constructor_2) ENABLED START -----*/
	init_device();
	/*----- PROTECTED REGION END -----*/	//	Lambda::constructor_2
}
//--------------------------------------------------------
Lambda::Lambda(Tango::DeviceClass *cl, const char *s, const char *d)
 : TANGO_BASE_CLASS(cl, s, d)
{
	/*----- PROTECTED REGION ID(Lambda::constructor_3) ENABLED START -----*/
	init_device();
	/*----- PROTECTED REGION END -----*/	//	Lambda::constructor_3
}

//--------------------------------------------------------
/**
 *	Method      : Lambda::delete_device()
 *	Description : will be called at device destruction or at init command
 */
//--------------------------------------------------------
void Lambda::delete_device()
{
	DEBUG_STREAM << "Lambda::delete_device() " << device_name << endl;
	/*----- PROTECTED REGION ID(Lambda::delete_device) ENABLED START -----*/
	
    //	Delete device allocated objects
    DELETE_SCALAR_ATTRIBUTE(attr_distortionCorrection_read);
    DELETE_SCALAR_ATTRIBUTE(attr_energyThreshold_read);
    DELETE_DEVSTRING_ATTRIBUTE(attr_configFilesPath_read);
	DELETE_SCALAR_ATTRIBUTE(attr_highVoltage_read);
	DELETE_SCALAR_ATTRIBUTE(attr_humidity_read);
	DELETE_SCALAR_ATTRIBUTE(attr_temperature_read);
	DELETE_DEVSTRING_ATTRIBUTE(attr_libraryVersion_read);


    m_is_device_initialized = false;

	/*----- PROTECTED REGION END -----*/	//	Lambda::delete_device
}

//--------------------------------------------------------
/**
 *	Method      : Lambda::init_device()
 *	Description : will be called at device initialization.
 */
//--------------------------------------------------------
void Lambda::init_device()
{
	DEBUG_STREAM << "Lambda::init_device() create device " << device_name << endl;
	/*----- PROTECTED REGION ID(Lambda::init_device_before) ENABLED START -----*/

	//	Initialization before get_device_property() call
	
	/*----- PROTECTED REGION END -----*/	//	Lambda::init_device_before
	

	//	Get the device properties from database
	get_device_property();
	
	/*----- PROTECTED REGION ID(Lambda::init_device) ENABLED START -----*/
    //	Initialize device
    CREATE_SCALAR_ATTRIBUTE(attr_distortionCorrection_read);
    CREATE_SCALAR_ATTRIBUTE(attr_energyThreshold_read);
    CREATE_DEVSTRING_ATTRIBUTE(attr_configFilesPath_read,Lambda_ns::STR_ATTR_SIZE_MAX);
    CREATE_SCALAR_ATTRIBUTE(attr_highVoltage_read);
    CREATE_SCALAR_ATTRIBUTE(attr_humidity_read);
    CREATE_SCALAR_ATTRIBUTE(attr_temperature_read);
    CREATE_DEVSTRING_ATTRIBUTE(attr_libraryVersion_read, Lambda_ns::STR_ATTR_SIZE_MAX);
    
    m_is_device_initialized = false;
    set_state(Tango::INIT);
    m_status_message.str("");


    try
	{
		//- get the main object used to pilot the lima framework		
		m_ct = ControlFactory::instance().get_control("Lambda");
		
		//- get interface to specific camera
		m_hw = dynamic_cast<lima::Lambda::Interface*>(m_ct->hwInterface());
		
		//- get camera to specific detector
		m_camera = &(m_hw->getCamera());
	}
	catch(Exception& e)
	{
		INFO_STREAM      << "Initialization Failed : " << e.getErrMsg() << endl;
		m_status_message << "Initialization Failed : " << e.getErrMsg( ) << endl;
		m_is_device_initialized = false;
		set_state(Tango::FAULT);
		return;
	}
	catch(...)
	{
		INFO_STREAM      << "Initialization Failed : UNKNOWN" << endl;
		m_status_message << "Initialization Failed : UNKNOWN" << endl;
		set_state(Tango::FAULT);
		m_is_device_initialized = false;
		return;
	}
    //	Initialize device
	m_is_device_initialized = true;
    try
	{
		// Update the hardware with the properties data
		write_at_init();
		m_camera->setDistortionCorrection(distortionCorrection);
		//- Get the lib version only once
		m_camera->getLibVersion(m_library_version);
	}
    catch(Tango::DevFailed& df)
	{
		ERROR_STREAM << df << endl;
		m_status_message << "Initialization Failed : ";
		for(unsigned i = 0;i < df.errors.length();i++)
		{
			m_status_message << df.errors[i].desc << endl;
		}
		m_is_device_initialized = false;
		set_state(Tango::FAULT);
		return;
	}
	catch(Exception& e)
	{
		ERROR_STREAM << "Initialization Failed : " << e.getErrMsg() << endl;
		m_status_message << "Initialization Failed : " << e.getErrMsg() << endl;
		m_is_device_initialized = false;
		set_state(Tango::FAULT);
		return;
	}
	dev_state();

	/*----- PROTECTED REGION END -----*/	//	Lambda::init_device
}

//--------------------------------------------------------
/**
 *	Method      : Lambda::get_device_property()
 *	Description : Read database to initialize property data members.
 */
//--------------------------------------------------------
void Lambda::get_device_property()
{
	/*----- PROTECTED REGION ID(Lambda::get_device_property_before) ENABLED START -----*/
	
	//	Initialize property data members
	
	/*----- PROTECTED REGION END -----*/	//	Lambda::get_device_property_before


	//	Read device properties from database.
	Tango::DbData	dev_prop;
	dev_prop.push_back(Tango::DbDatum("ConfigFilesPath"));
	dev_prop.push_back(Tango::DbDatum("DistortionCorrection"));
	dev_prop.push_back(Tango::DbDatum("MemorizedEnergyThreshold"));

	//	is there at least one property to be read ?
	if (dev_prop.size()>0)
	{
		//	Call database and extract values
		if (Tango::Util::instance()->_UseDb==true)
			get_db_device()->get_property(dev_prop);
	
		//	get instance on LambdaClass to get class property
		Tango::DbDatum	def_prop, cl_prop;
		LambdaClass	*ds_class =
			(static_cast<LambdaClass *>(get_device_class()));
		int	i = -1;

		//	Try to initialize ConfigFilesPath from class property
		cl_prop = ds_class->get_class_property(dev_prop[++i].name);
		if (cl_prop.is_empty()==false)	cl_prop  >>  configFilesPath;
		else {
			//	Try to initialize ConfigFilesPath from default device value
			def_prop = ds_class->get_default_device_property(dev_prop[i].name);
			if (def_prop.is_empty()==false)	def_prop  >>  configFilesPath;
		}
		//	And try to extract ConfigFilesPath value from database
		if (dev_prop[i].is_empty()==false)	dev_prop[i]  >>  configFilesPath;

		//	Try to initialize DistortionCorrection from class property
		cl_prop = ds_class->get_class_property(dev_prop[++i].name);
		if (cl_prop.is_empty()==false)	cl_prop  >>  distortionCorrection;
		else {
			//	Try to initialize DistortionCorrection from default device value
			def_prop = ds_class->get_default_device_property(dev_prop[i].name);
			if (def_prop.is_empty()==false)	def_prop  >>  distortionCorrection;
		}
		//	And try to extract DistortionCorrection value from database
		if (dev_prop[i].is_empty()==false)	dev_prop[i]  >>  distortionCorrection;

		//	Try to initialize MemorizedEnergyThreshold from class property
		cl_prop = ds_class->get_class_property(dev_prop[++i].name);
		if (cl_prop.is_empty()==false)	cl_prop  >>  memorizedEnergyThreshold;
		else {
			//	Try to initialize MemorizedEnergyThreshold from default device value
			def_prop = ds_class->get_default_device_property(dev_prop[i].name);
			if (def_prop.is_empty()==false)	def_prop  >>  memorizedEnergyThreshold;
		}
		//	And try to extract MemorizedEnergyThreshold value from database
		if (dev_prop[i].is_empty()==false)	dev_prop[i]  >>  memorizedEnergyThreshold;

	}

	/*----- PROTECTED REGION ID(Lambda::get_device_property_after) ENABLED START -----*/
	
	//	Check device property data members init
	yat4tango::PropertyHelper::create_property_if_empty(this, dev_prop, "/opt/xsp/config", "ConfigFilesPath"              );
	yat4tango::PropertyHelper::create_property_if_empty(this, dev_prop, "True"  , "DistortionCorrection");
	yat4tango::PropertyHelper::create_property_if_empty(this, dev_prop, "2.0", "MemorizedEnergyThreshold"    );
	/*----- PROTECTED REGION END -----*/	//	Lambda::get_device_property_after
}

//--------------------------------------------------------
/**
 *	Method      : Lambda::always_executed_hook()
 *	Description : method always executed before any command is executed
 */
//--------------------------------------------------------
void Lambda::always_executed_hook()
{
	DEBUG_STREAM << "Lambda::always_executed_hook()  " << device_name << endl;
	/*----- PROTECTED REGION ID(Lambda::always_executed_hook) ENABLED START -----*/
	
	//	code always executed before all requests
    try
    {
        m_status_message.str("");

        //update state
        dev_state();
    }
    catch (Exception& e)
    {
        ERROR_STREAM << e.getErrMsg() << endl;
        m_status_message << "always_executed_hook : " << e.getErrMsg() << endl;
        //- throw exception
        set_state(Tango::FAULT);
        m_is_device_initialized = false;
        return;
    }
    catch (...)
    {
        ERROR_STREAM << "always_executed_hook : UNKNOWN" << endl;
        m_status_message << "always_executed_hook : UNKNOWN" << endl;
        //- throw exception
        set_state(Tango::FAULT);
        m_is_device_initialized = false;
        return;
    }
	
	/*----- PROTECTED REGION END -----*/	//	Lambda::always_executed_hook
}

//--------------------------------------------------------
/**
 *	Method      : Lambda::read_attr_hardware()
 *	Description : Hardware acquisition for attributes
 */
//--------------------------------------------------------
void Lambda::read_attr_hardware(TANGO_UNUSED(vector<long> &attr_list))
{
	DEBUG_STREAM << "Lambda::read_attr_hardware(vector<long> &attr_list) entering... " << endl;
	/*----- PROTECTED REGION ID(Lambda::read_attr_hardware) ENABLED START -----*/
	
	//	Add your own code
	
	/*----- PROTECTED REGION END -----*/	//	Lambda::read_attr_hardware
}
//--------------------------------------------------------
/**
 *	Method      : Lambda::write_attr_hardware()
 *	Description : Hardware writing for attributes
 */
//--------------------------------------------------------
void Lambda::write_attr_hardware(TANGO_UNUSED(vector<long> &attr_list))
{
	DEBUG_STREAM << "Lambda::write_attr_hardware(vector<long> &attr_list) entering... " << endl;
	/*----- PROTECTED REGION ID(Lambda::write_attr_hardware) ENABLED START -----*/
	
	//	Add your own code
	
	/*----- PROTECTED REGION END -----*/	//	Lambda::write_attr_hardware
}

//--------------------------------------------------------
/**
 *	Read attribute configFilesPath related method
 *	Description: Path of configuration file.
 *
 *	Data type:	Tango::DevString
 *	Attr type:	Scalar
 */
//--------------------------------------------------------
void Lambda::read_configFilesPath(Tango::Attribute &attr)
{
	DEBUG_STREAM << "Lambda::read_configFilesPath(Tango::Attribute &attr) entering... " << endl;
	/*----- PROTECTED REGION ID(Lambda::read_configFilesPath) ENABLED START -----*/
    try
    {
       	const char* temp = configFilesPath.c_str();
        strcpy(*attr_configFilesPath_read, temp);
    	attr.set_value(attr_configFilesPath_read);
    }
    catch (Tango::DevFailed& df)
    {
        manage_devfailed_exception(df, "read_configFilesPath");
    }
	catch (lima::Exception& le)
    {
        manage_lima_exception(le, "read_configFilesPath");
    }
	

	/*----- PROTECTED REGION END -----*/	//	Lambda::read_configFilesPath
}
//--------------------------------------------------------
/**
 *	Read attribute distortionCorrection related method
 *	Description: get distortion correction.<br>
 *               When distortion correction is enabled :<br>
 *               - Large pixels are divided according to predefined denominator. <br>
 *               - The values of the pixels are rounded during division. <br>
 *               - If pixel value is saturated, the division is not applied.<br>
 *
 *	Data type:	Tango::DevBoolean
 *	Attr type:	Scalar
 */
//--------------------------------------------------------
void Lambda::read_distortionCorrection(Tango::Attribute &attr)
{
	DEBUG_STREAM << "Lambda::read_distortionCorrection(Tango::Attribute &attr) entering... " << endl;
	/*----- PROTECTED REGION ID(Lambda::read_distortionCorrection) ENABLED START -----*/
    try
    {
        m_camera->getDistortionCorrection(*attr_distortionCorrection_read);
        attr.set_value(attr_distortionCorrection_read);
    }
    catch (Tango::DevFailed& df)
    {
        manage_devfailed_exception(df, "read_distortionCorrection");
    }
	catch (lima::Exception& le)
    {
        manage_lima_exception(le, "read_distortionCorrection");
    }

	/*----- PROTECTED REGION END -----*/	//	Lambda::read_distortionCorrection
}
//--------------------------------------------------------
/**
 *	Read attribute energyThreshold related method
 *	Description: set/get first energy threshold in eV.<br>
 *               The photon is counted If the energy is above this threshold.<br>
 *
 *	Data type:	Tango::DevDouble
 *	Attr type:	Scalar
 */
//--------------------------------------------------------
void Lambda::read_energyThreshold(Tango::Attribute &attr)
{
	DEBUG_STREAM << "Lambda::read_energyThreshold(Tango::Attribute &attr) entering... " << endl;
	/*----- PROTECTED REGION ID(Lambda::read_energyThreshold) ENABLED START -----*/
	try
    {
		m_camera->getEnergyThreshold(*attr_energyThreshold_read);
		attr.set_value(attr_energyThreshold_read);
    }
    catch (Tango::DevFailed& df)
    {
        manage_devfailed_exception(df, "read_energyThreshold");
    }
	catch (lima::Exception& le)
    {
        manage_lima_exception(le, "read_energyThreshold");
    }

	/*----- PROTECTED REGION END -----*/	//	Lambda::read_energyThreshold
}
//--------------------------------------------------------
/**
 *	Write attribute energyThreshold related method
 *	Description: set/get first energy threshold in eV.<br>
 *               The photon is counted If the energy is above this threshold.<br>
 *
 *	Data type:	Tango::DevDouble
 *	Attr type:	Scalar
 */
//--------------------------------------------------------
void Lambda::write_energyThreshold(Tango::WAttribute &attr)
{
	DEBUG_STREAM << "Lambda::write_energyThreshold(Tango::WAttribute &attr) entering... " << endl;
	//	Retrieve write value
	Tango::DevDouble	w_val;
	attr.get_write_value(w_val);
	/*----- PROTECTED REGION ID(Lambda::write_energyThreshold) ENABLED START -----*/
	try
    {
        m_camera->setEnergyThreshold(w_val);
    }
    catch (Tango::DevFailed& df)
    {
        manage_devfailed_exception(df, "write_energyThreshold");
    }
	catch (lima::Exception& le)
    {
        manage_lima_exception(le, "write_energyThreshold");
    }
	
	/*----- PROTECTED REGION END -----*/	//	Lambda::write_energyThreshold
}
//--------------------------------------------------------
/**
 *	Read attribute libraryVersion related method
 *	Description: 
 *
 *	Data type:	Tango::DevString
 *	Attr type:	Scalar
 */
//--------------------------------------------------------
void Lambda::read_libraryVersion(Tango::Attribute &attr)
{
	DEBUG_STREAM << "Lambda::read_libraryVersion(Tango::Attribute &attr) entering... " << endl;
	/*----- PROTECTED REGION ID(Lambda::read_libraryVersion) ENABLED START -----*/
	try
    {
		strcpy(*attr_libraryVersion_read, m_library_version.c_str());
		attr.set_value(attr_libraryVersion_read);
    }
    catch (Tango::DevFailed& df)
    {
        manage_devfailed_exception(df, "read_libraryVersion");
    }
    catch (lima::Exception& le)
    {
        manage_lima_exception(le, "read_libraryVersion");
    }

	/*----- PROTECTED REGION END -----*/	//	Lambda::read_libraryVersion
}
//--------------------------------------------------------
/**
 *	Read attribute highVoltage related method
 *	Description: 
 *
 *	Data type:	Tango::DevDouble
 *	Attr type:	Scalar
 */
//--------------------------------------------------------
void Lambda::read_highVoltage(Tango::Attribute &attr)
{
	DEBUG_STREAM << "Lambda::read_highVoltage(Tango::Attribute &attr) entering... " << endl;
	/*----- PROTECTED REGION ID(Lambda::read_highVoltage) ENABLED START -----*/
	try
    {
		//the function "hasFeature" returns a boolean depending on the compatibility between the code and the firmware:
		//if the this function returns false it means that this functionnality is not supported by the firmware.
		if (m_camera->hasFeature(xsp::lambda::Feature::FEAT_HV))
		{
			m_camera->getHighVoltage(*attr_highVoltage_read);
    		attr.set_value(attr_highVoltage_read);
		}
		else 
		{
			attr.set_quality(Tango::ATTR_INVALID);
		}
        
    }
    catch (Tango::DevFailed& df)
    {
        manage_devfailed_exception(df, "read_highVoltage");
    }
    catch (lima::Exception& le)
    {
        manage_lima_exception(le, "read_highVoltage");
    }

	/*----- PROTECTED REGION END -----*/	//	Lambda::read_highVoltage
}
//--------------------------------------------------------
/**
 *	Read attribute humidity related method
 *	Description: 
 *
 *	Data type:	Tango::DevDouble
 *	Attr type:	Scalar
 */
//--------------------------------------------------------
void Lambda::read_humidity(Tango::Attribute &attr)
{
	DEBUG_STREAM << "Lambda::read_humidity(Tango::Attribute &attr) entering... " << endl;
	/*----- PROTECTED REGION ID(Lambda::read_humidity) ENABLED START -----*/
	try
    {
        m_camera->getHumidity(*attr_humidity_read);

		//if the humidity returns 0.0 it means that this function is not supported by the firmware.
		if (*attr_humidity_read == 0.0)
		{
			attr.set_quality(Tango::ATTR_INVALID);
		}
		else 
		{
			attr.set_value(attr_humidity_read);
		}
    }
    catch (Tango::DevFailed& df)
    {
        manage_devfailed_exception(df, "read_humidity");
    }
	catch (lima::Exception& le)
    {
        manage_lima_exception(le, "read_humidity");
    }
	
	/*----- PROTECTED REGION END -----*/	//	Lambda::read_humidity
}
//--------------------------------------------------------
/**
 *	Read attribute temperature related method
 *	Description: 
 *
 *	Data type:	Tango::DevDouble
 *	Attr type:	Scalar
 */
//--------------------------------------------------------
void Lambda::read_temperature(Tango::Attribute &attr)
{
	DEBUG_STREAM << "Lambda::read_temperature(Tango::Attribute &attr) entering... " << endl;
	/*----- PROTECTED REGION ID(Lambda::read_temperature) ENABLED START -----*/
	
	try
    {
        m_camera->getTemperature(*attr_temperature_read);

		// if the temperature returns 0 it means that this function is not supported by the firmware.
		if (*attr_temperature_read == 0)
		{
			attr.set_quality(Tango::ATTR_INVALID);
		}
		else
		{
    		attr.set_value(attr_temperature_read);
		}
    }
    catch (Tango::DevFailed& df)
    {
        manage_devfailed_exception(df, "read_temperature");
    }
	catch (lima::Exception& le)
    {
        manage_lima_exception(le, "read_temperature");
    }
	
	/*----- PROTECTED REGION END -----*/	//	Lambda::read_temperature
}

//--------------------------------------------------------
/**
 *	Method      : Lambda::add_dynamic_attributes()
 *	Description : Create the dynamic attributes if any
 *                for specified device.
 */
//--------------------------------------------------------
void Lambda::add_dynamic_attributes()
{
	/*----- PROTECTED REGION ID(Lambda::add_dynamic_attributes) ENABLED START -----*/
	
	//	Add your own code to create and add dynamic attributes if any
	
	/*----- PROTECTED REGION END -----*/	//	Lambda::add_dynamic_attributes
}

//--------------------------------------------------------
/**
 *	Method      : Lambda::add_dynamic_commands()
 *	Description : Create the dynamic commands if any
 *                for specified device.
 */
//--------------------------------------------------------
void Lambda::add_dynamic_commands()
{
	/*----- PROTECTED REGION ID(Lambda::add_dynamic_commands) ENABLED START -----*/
	
	//	Add your own code to create and add dynamic commands if any
	
	/*----- PROTECTED REGION END -----*/	//	Lambda::add_dynamic_commands
}

/*----- PROTECTED REGION ID(Lambda::namespace_ending) ENABLED START -----*/

//	Additional Methods
//+------------------------------------------------------------------
/**
 *	method:	Lambda::dev_state
 *
 *	description:	method to execute "State"
 *	This command gets the device state (stored in its <i>device_state</i> data member) and returns it to the caller.
 *
 * @return	State Code
 *
 */
//+------------------------------------------------------------------
Tango::DevState Lambda::dev_state()
{
    Tango::DevState	argout = DeviceImpl::dev_state();
    DEBUG_STREAM << "Lambda::dev_state(): entering... !" << endl;

    // Add your own code to control device here
    stringstream DeviceStatus;
    DeviceStatus << "";
    Tango::DevState DeviceState = Tango::STANDBY;

    if(!m_is_device_initialized )
    {
        DeviceState  = Tango::FAULT;
        DeviceStatus << m_status_message.str();
    }
    else
    {
        // state & status are retrieved from Factory, Factory is updated by Generic device
        DeviceState = ControlFactory::instance().get_state();
        DeviceStatus << ControlFactory::instance().get_status();
    }

    set_state (DeviceState);
    set_status(DeviceStatus.str());

    return DeviceState;
}

//+------------------------------------------------------------------
/**
 *	method:	Lambda::manage_devfailed_exception
 *
 *	description: method which manages DevFailed exceptions
 */
//+------------------------------------------------------------------
void Lambda::manage_devfailed_exception(Tango::DevFailed & in_exception, const std::string & in_caller_method_name)
{
    ERROR_STREAM << in_exception << endl;
	
    // rethrow exception
    Tango::Except::re_throw_exception(in_exception,
                                      "TANGO_DEVICE_ERROR",
                                      string(in_exception.errors[0].desc).c_str(),
                                      in_caller_method_name.c_str());
}

//+------------------------------------------------------------------
/**
 *	method:	Lambda::manage_lima_exception
 *
 *	description: method which manages lima exceptions
 */
//+------------------------------------------------------------------
void Lambda::manage_lima_exception(lima::Exception & in_exception, const std::string & in_caller_method_name)
{
    ERROR_STREAM << in_exception.getErrMsg() << endl;

    // throw exception
    Tango::Except::throw_exception("TANGO_DEVICE_ERROR",
                                   in_exception.getErrMsg().c_str(),
                                   in_caller_method_name.c_str());
}


/*****************************************************************************
 * \brief Update the hardware with the properties data
 *****************************************************************************/
void Lambda::write_at_init(void)
{
    INFO_STREAM << "Write tango hardware at Init - energyThreshold." << endl;
	Tango::WAttribute &energyThreshold = dev_attr->get_w_attr_by_name("energyThreshold");
	attr_energyThreshold_write = memorizedEnergyThreshold;
	energyThreshold.set_write_value(attr_energyThreshold_write);
	write_energyThreshold(energyThreshold);

}
/*----- PROTECTED REGION END -----*/	//	Lambda::namespace_ending
} //	namespace
