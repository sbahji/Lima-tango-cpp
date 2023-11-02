/*----- PROTECTED REGION ID(Dhyana6060.cpp) ENABLED START -----*/
//=============================================================================
//
// file :        Dhyana6060.cpp
//
// description : C++ source for the Dhyana6060 class and its commands.
//               The class is derived from Device. It represents the
//               CORBA servant object which will be accessed from the
//               network. All commands which can be executed on the
//               Dhyana6060 are implemented in this file.
//
// project :     
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
//
//
//=============================================================================
//                This file is generated by POGO
//        (Program Obviously used to Generate tango Object)
//=============================================================================


#include <Dhyana6060.h>
#include <Dhyana6060Class.h>

#include "AttrViewDhyana6060.h"

/*----- PROTECTED REGION END -----*/	//	Dhyana6060.cpp

/**
 *  Dhyana6060 class description:
 *    
 */

//================================================================
//  The following table gives the correspondence
//  between command and method names.
//
//  Command name      |  Method name
//================================================================
//  State             |  Inherited (no method)
//  Status            |  Inherited (no method)
//  GetAllParameters  |  get_all_parameters
//  GetParameter      |  get_parameter
//  SetParameter      |  set_parameter
//================================================================

//================================================================
//  Attributes managed is:
//================================================================
//================================================================

namespace Dhyana6060_ns
{
/*----- PROTECTED REGION ID(Dhyana6060::namespace_starting) ENABLED START -----*/

//	static initializations

/*----- PROTECTED REGION END -----*/	//	Dhyana6060::namespace_starting

//--------------------------------------------------------
/**
 *	Method      : Dhyana6060::Dhyana6060()
 *	Description : Constructors for a Tango device
 *                implementing the classDhyana6060
 */
//--------------------------------------------------------
Dhyana6060::Dhyana6060(Tango::DeviceClass *cl, string &s)
 : TANGO_BASE_CLASS(cl, s.c_str())
{
	/*----- PROTECTED REGION ID(Dhyana6060::constructor_1) ENABLED START -----*/
	init_device();
	
	/*----- PROTECTED REGION END -----*/	//	Dhyana6060::constructor_1
}
//--------------------------------------------------------
Dhyana6060::Dhyana6060(Tango::DeviceClass *cl, const char *s)
 : TANGO_BASE_CLASS(cl, s)
{
	/*----- PROTECTED REGION ID(Dhyana6060::constructor_2) ENABLED START -----*/
	init_device();
	
	/*----- PROTECTED REGION END -----*/	//	Dhyana6060::constructor_2
}
//--------------------------------------------------------
Dhyana6060::Dhyana6060(Tango::DeviceClass *cl, const char *s, const char *d)
 : TANGO_BASE_CLASS(cl, s, d)
{
	/*----- PROTECTED REGION ID(Dhyana6060::constructor_3) ENABLED START -----*/
	init_device();
	
	/*----- PROTECTED REGION END -----*/	//	Dhyana6060::constructor_3
}

//--------------------------------------------------------
/**
 *	Method      : Dhyana6060::delete_device()
 *	Description : will be called at device destruction or at init command
 */
//--------------------------------------------------------
void Dhyana6060::delete_device()
{
	DEBUG_STREAM << "Dhyana6060::delete_device() " << device_name << endl;
	/*----- PROTECTED REGION ID(Dhyana6060::delete_device) ENABLED START -----*/
	
	//	Delete device allocated objects
	
	/*----- PROTECTED REGION END -----*/	//	Dhyana6060::delete_device
}

//--------------------------------------------------------
/**
 *	Method      : Dhyana6060::init_device()
 *	Description : will be called at device initialization.
 */
//--------------------------------------------------------
void Dhyana6060::init_device()
{
	DEBUG_STREAM << "Dhyana6060::init_device() create device " << device_name << endl;
	/*----- PROTECTED REGION ID(Dhyana6060::init_device_before) ENABLED START -----*/
	
	//	Initialization before get_device_property() call
	
	/*----- PROTECTED REGION END -----*/	//	Dhyana6060::init_device_before
	
	//	No device property to be read from database
	
	/*----- PROTECTED REGION ID(Dhyana6060::init_device) ENABLED START -----*/
	
	//	Initialize device
	m_is_device_initialized = false;
	set_state(Tango::INIT);

	try
	{
		//- get the main object used to pilot the lima framework
		//in fact LimaDetector is create the singleton control objet
		//so this call, will only return existing object, no need to give it the ip !!
		m_ct = ControlFactory::instance().get_control("Dhyana6060");

		//- get interface to specific camera
		m_hw = dynamic_cast<lima::Dhyana6060::Interface*> (m_ct->hwInterface());

		//- get camera to specific detector
		m_camera = &(m_hw->getCamera());
		
		build_view();
	}
	catch(lima::Exception& e)
	{
		ERROR_STREAM << "Initialization Failed : " << e.getErrMsg() << endl;
		m_is_device_initialized = false;
		set_state(Tango::FAULT);
		return;
	}
	catch(...)
	{
		ERROR_STREAM << "Initialization Failed : UNKNOWN" << endl;
		set_state(Tango::FAULT);
		m_is_device_initialized = false;
		return;
	}

	m_is_device_initialized = true;
	

	set_state(Tango::STANDBY);
	dev_state();
	write_attr_at_init();
	
	/*----- PROTECTED REGION END -----*/	//	Dhyana6060::init_device
}


//--------------------------------------------------------
/**
 *	Method      : Dhyana6060::always_executed_hook()
 *	Description : method always executed before any command is executed
 */
//--------------------------------------------------------
void Dhyana6060::always_executed_hook()
{
	DEBUG_STREAM << "Dhyana6060::always_executed_hook()  " << device_name << endl;
	/*----- PROTECTED REGION ID(Dhyana6060::always_executed_hook) ENABLED START -----*/
	
	//	code always executed before all requests
	
	/*----- PROTECTED REGION END -----*/	//	Dhyana6060::always_executed_hook
}

//--------------------------------------------------------
/**
 *	Method      : Dhyana6060::read_attr_hardware()
 *	Description : Hardware acquisition for attributes
 */
//--------------------------------------------------------
void Dhyana6060::read_attr_hardware(TANGO_UNUSED(vector<long> &attr_list))
{
	DEBUG_STREAM << "Dhyana6060::read_attr_hardware(vector<long> &attr_list) entering... " << endl;
	/*----- PROTECTED REGION ID(Dhyana6060::read_attr_hardware) ENABLED START -----*/
	
	//	Add your own code
	
	/*----- PROTECTED REGION END -----*/	//	Dhyana6060::read_attr_hardware
}


//--------------------------------------------------------
/**
 *	Method      : Dhyana6060::add_dynamic_attributes()
 *	Description : Create the dynamic attributes if any
 *                for specified device.
 */
//--------------------------------------------------------
void Dhyana6060::add_dynamic_attributes()
{
	/*----- PROTECTED REGION ID(Dhyana6060::add_dynamic_attributes) ENABLED START -----*/
	
	//	Add your own code to create and add dynamic attributes if any
	
	/*----- PROTECTED REGION END -----*/	//	Dhyana6060::add_dynamic_attributes
}

//--------------------------------------------------------
/**
 *	Command GetAllParameters related method
 *	Description: Return the list of all the camera available parameters and their values in the following format:
 *               ParameterName=current_value
 *
 *	@returns 
 */
//--------------------------------------------------------
Tango::DevString Dhyana6060::get_all_parameters()
{
	Tango::DevString argout;
	DEBUG_STREAM << "Dhyana6060::GetAllParameters()  - " << device_name << endl;
	/*----- PROTECTED REGION ID(Dhyana6060::get_all_parameters) ENABLED START -----*/
	
	//	Add your own code
	try
	{
        argout = CORBA::string_dup(m_camera->getAllParameters().c_str());
	}
	catch(Tango::DevFailed& df)
    {
        ERROR_STREAM << df << endl;
        //- rethrow exception
		Tango::Except::re_throw_exception(df,
										"TANGO_DEVICE_ERROR",
										std::string(df.errors[0].desc).c_str(),
										"Dhyana::get_all_parameters");
    }		
    catch(lima::Exception& e)
    {
        ERROR_STREAM << e.getErrMsg() << endl;
        //- throw exception
        Tango::Except::throw_exception("TANGO_DEVICE_ERROR",
										e.getErrMsg().c_str(),
										"Dhyana::get_all_parameters");
    }
	
	/*----- PROTECTED REGION END -----*/	//	Dhyana6060::get_all_parameters
	return argout;
}
//--------------------------------------------------------
/**
 *	Command GetParameter related method
 *	Description: Return the current value of the specified parameter
 *
 *	@param argin 
 *	@returns 
 */
//--------------------------------------------------------
Tango::DevString Dhyana6060::get_parameter(Tango::DevString argin)
{
	Tango::DevString argout;
	DEBUG_STREAM << "Dhyana6060::GetParameter()  - " << device_name << endl;
	/*----- PROTECTED REGION ID(Dhyana6060::get_parameter) ENABLED START -----*/
	
	//	Add your own code
	try
	{
        argout = CORBA::string_dup(m_camera->getParameter(argin).c_str());      
	}
	catch(Tango::DevFailed& df)
    {
        ERROR_STREAM << df << endl;
        //- rethrow exception
		Tango::Except::re_throw_exception(df,
										"TANGO_DEVICE_ERROR",
										std::string(df.errors[0].desc).c_str(),
										"Dhyana::get_parameter");
					
    }		
    catch(lima::Exception& e)
    {
        ERROR_STREAM << e.getErrMsg() << endl;
        //- throw exception
        Tango::Except::throw_exception("TANGO_DEVICE_ERROR",
										e.getErrMsg().c_str(),
										"Dhyana::get_parameter");
    }
	
	/*----- PROTECTED REGION END -----*/	//	Dhyana6060::get_parameter
	return argout;
}
//--------------------------------------------------------
/**
 *	Command SetParameter related method
 *	Description: Set the value of the specified parameter.
 *
 *	@param argin 
 */
//--------------------------------------------------------
void Dhyana6060::set_parameter(const Tango::DevVarStringArray *argin)
{
	DEBUG_STREAM << "Dhyana6060::SetParameter()  - " << device_name << endl;
	/*----- PROTECTED REGION ID(Dhyana6060::set_parameter) ENABLED START -----*/
	
	//	Add your own code
	if(argin->length() != 2)
	{
		//- throw exception
		Tango::Except::throw_exception("TANGO_DEVICE_ERROR",
										"Invalid number of parameters. Check input parameters (parameter, value)\n",
										"Dhyana::set_parameter");
	}
    try
    {
		std::string parameter = static_cast<std::string>((*argin)[0]);
		std::string value_str = static_cast<std::string>((*argin)[1]);
		m_camera->setParameter(parameter, std::stod(value_str));
    }
    catch(Tango::DevFailed& df)
    {
        ERROR_STREAM << df << endl;
        //- rethrow exception
		Tango::Except::re_throw_exception(df,
										"TANGO_DEVICE_ERROR",
										std::string(df.errors[0].desc).c_str(),
										"Dhyana::set_parameter");
    }		
    catch(lima::Exception& e)
    {
        ERROR_STREAM << e.getErrMsg() << endl;
        //- throw exception
        Tango::Except::throw_exception("TANGO_DEVICE_ERROR",
										e.getErrMsg().c_str(),
										"Dhyana::set_parameter");
    }
	
	/*----- PROTECTED REGION END -----*/	//	Dhyana6060::set_parameter
}
//--------------------------------------------------------
/**
 *	Method      : Dhyana6060::add_dynamic_commands()
 *	Description : Create the dynamic commands if any
 *                for specified device.
 */
//--------------------------------------------------------
void Dhyana6060::add_dynamic_commands()
{
	/*----- PROTECTED REGION ID(Dhyana6060::add_dynamic_commands) ENABLED START -----*/
	
	//	Add your own code to create and add dynamic commands if any
	
	/*----- PROTECTED REGION END -----*/	//	Dhyana6060::add_dynamic_commands
}

/*----- PROTECTED REGION ID(Dhyana6060::namespace_ending) ENABLED START -----*/

//	Additional Methods
bool Dhyana6060::is_device_initialized()
{
	return m_is_device_initialized;
}

lima::Dhyana6060::Camera* Dhyana6060::get_camera()
{
	return m_camera;
}


void Dhyana6060::build_view()
{
	m_attr_view.reset(new AttrViewDhyana6060(this));
}

//-------------------------------------
// Dhyana6060::write_attr_at_init()
//-------------------------------------
void Dhyana6060::write_attr_at_init()
{
	try
	{

		INFO_STREAM << "Write tango attribute at Init - sensorTemperatureTarget." << endl;
		Tango::WAttribute &temperatureTarget = dev_attr->get_w_attr_by_name("sensorTemperatureTarget");
		double target = yat4tango::PropertyHelper::get_memorized_attribute<Tango::DevEnum>(this, "sensorTemperatureTarget", 0);
		temperatureTarget.set_write_value(target);
		yat4tango::DynamicAttributeWriteCallbackData cbd_temperatureTarget;
		cbd_temperatureTarget.tga = &temperatureTarget;
		cbd_temperatureTarget.dya = &m_attr_view->get_dim()->dynamic_attributes_manager().get_attribute("sensorTemperatureTarget");
		m_attr_view->write_dynamic_cooling_attribute_callback(cbd_temperatureTarget);

		INFO_STREAM << "Write tango attribute at Init - sensorCoolingType." << endl;
		Tango::WAttribute &sensorCoolingType = dev_attr->get_w_attr_by_name("sensorCoolingType");
		Tango::DevEnum coolingType = yat4tango::PropertyHelper::get_memorized_attribute<Tango::DevEnum>(this, "sensorCoolingType", 1);
		sensorCoolingType.set_write_value(coolingType);
		yat4tango::DynamicAttributeWriteCallbackData cbd_sensorCoolingType;
		cbd_sensorCoolingType.tga = &sensorCoolingType;
		cbd_sensorCoolingType.dya = &m_attr_view->get_dim()->dynamic_attributes_manager().get_attribute("sensorCoolingType");
		m_attr_view->write_dynamic_cooling_attribute_callback(cbd_sensorCoolingType);

		INFO_STREAM << "Write tango attribute at Init - fanSpeed." << endl;
		Tango::WAttribute &fanSpeed = dev_attr->get_w_attr_by_name("fanSpeed");
		unsigned short speed = yat4tango::PropertyHelper::get_memorized_attribute<Tango::DevUShort>(this, "fanSpeed", 0);
		fanSpeed.set_write_value(speed);
		if (coolingType == 0) // if coolingType == FanCool
		{
			yat4tango::DynamicAttributeWriteCallbackData cbd_fanSpeed;
			cbd_fanSpeed.tga = &fanSpeed;
			cbd_fanSpeed.dya = &m_attr_view->get_dim()->dynamic_attributes_manager().get_attribute("fanSpeed");
			m_attr_view->write_dynamic_cooling_attribute_callback(cbd_fanSpeed);
		}

		INFO_STREAM << "Write tango attribute at Init - fanType." << endl;
		Tango::WAttribute &fanType = dev_attr->get_w_attr_by_name("fanType");
		short type = yat4tango::PropertyHelper::get_memorized_attribute<Tango::DevUShort>(this, "fanType", 0);
		fanType.set_write_value(type);
		if (coolingType == 0) // if coolingType == FanCool
		{
			yat4tango::DynamicAttributeWriteCallbackData cbd_fanType;
			cbd_fanType.tga = &fanType;
			cbd_fanType.dya = &m_attr_view->get_dim()->dynamic_attributes_manager().get_attribute("fanType");
			m_attr_view->write_dynamic_cooling_attribute_callback(cbd_fanType);
		}


		INFO_STREAM << "Write tango attribute at Init - globalGain." << endl;
		Tango::WAttribute &globalGain = dev_attr->get_w_attr_by_name("globalGain");
		Tango::DevEnum gain = yat4tango::PropertyHelper::get_memorized_attribute<Tango::DevEnum>(this, "globalGain", 0);
		globalGain.set_write_value(gain);
		yat4tango::DynamicAttributeWriteCallbackData cbd_globalGain;
		cbd_globalGain.tga = &globalGain;
		cbd_globalGain.dya = &m_attr_view->get_dim()->dynamic_attributes_manager().get_attribute("globalGain");
		m_attr_view->write_dynamic_attribute_callback(cbd_globalGain);

		std::string name = "trigOutputPort";
		INFO_STREAM << "Write tango attribute at Init - " << name << endl;
		Tango::WAttribute &trigOutputPort = dev_attr->get_w_attr_by_name(name.c_str());
		Tango::DevEnum port = yat4tango::PropertyHelper::get_memorized_attribute<Tango::DevEnum>(this, name, 0);
		trigOutputPort.set_write_value(port);
		yat4tango::DynamicAttributeWriteCallbackData cbd_trigOutputPort;
		cbd_trigOutputPort.tga = &trigOutputPort;
		cbd_trigOutputPort.dya = &m_attr_view->get_dim()->dynamic_attributes_manager().get_attribute(name);
		m_attr_view->write_dynamic_trigger_attribute_callback(cbd_trigOutputPort);


		name = "trigOutputKind";
		INFO_STREAM << "Write tango attribute at Init - " << name << endl;
		Tango::WAttribute &trigOutputKind = dev_attr->get_w_attr_by_name(name.c_str());
		Tango::DevEnum kind = yat4tango::PropertyHelper::get_memorized_attribute<Tango::DevEnum>(this, name, 0);
		trigOutputKind.set_write_value(kind);
		yat4tango::DynamicAttributeWriteCallbackData cbd_trigOutputKind;
		cbd_trigOutputKind.tga = &trigOutputKind;
		cbd_trigOutputKind.dya = &m_attr_view->get_dim()->dynamic_attributes_manager().get_attribute(name);
		m_attr_view->write_dynamic_trigger_attribute_callback(cbd_trigOutputKind);

		name = "trigOutputWidth";
		INFO_STREAM << "Write tango attribute at Init - " << name << endl;
		Tango::WAttribute &trigOutputWidth = dev_attr->get_w_attr_by_name(name.c_str());
		double width = yat4tango::PropertyHelper::get_memorized_attribute<Tango::DevDouble>(this, name, 5000);
		trigOutputWidth.set_write_value(width);
		if (kind == 2 || kind == 4) // kind = ExposureStart or kind = ReadoutEnd
		{
			yat4tango::DynamicAttributeWriteCallbackData cbd_trigOutputWidth;
			cbd_trigOutputWidth.tga = &trigOutputWidth;
			cbd_trigOutputWidth.dya = &m_attr_view->get_dim()->dynamic_attributes_manager().get_attribute(name);
			m_attr_view->write_dynamic_trigger_attribute_callback(cbd_trigOutputWidth);
		}

		name = "trigOutputDelay";
		INFO_STREAM << "Write tango attribute at Init - " << name << endl;
		Tango::WAttribute &trigOutputDelay = dev_attr->get_w_attr_by_name(name.c_str());
		double delay = yat4tango::PropertyHelper::get_memorized_attribute<Tango::DevDouble>(this, name, 0);
		trigOutputDelay.set_write_value(delay);
		if (kind != 0 && kind != 1) //kind different from low and high
		{
			yat4tango::DynamicAttributeWriteCallbackData cbd_trigOutputDelay;
			cbd_trigOutputDelay.tga = &trigOutputDelay;
			cbd_trigOutputDelay.dya = &m_attr_view->get_dim()->dynamic_attributes_manager().get_attribute(name);
			m_attr_view->write_dynamic_trigger_attribute_callback(cbd_trigOutputDelay);
		}

		name = "trigOutputEdge";
		INFO_STREAM << "Write tango attribute at Init - " << name << endl;
		Tango::WAttribute &trigOutputEdge = dev_attr->get_w_attr_by_name(name.c_str());
		Tango::DevEnum edge = yat4tango::PropertyHelper::get_memorized_attribute<Tango::DevEnum>(this, name, 0);
		trigOutputEdge.set_write_value(edge);
		if (kind != 0 && kind != 1) //kind different from low and high
		{
			yat4tango::DynamicAttributeWriteCallbackData cbd_trigOutputEdge;
			cbd_trigOutputEdge.tga = &trigOutputEdge;
			cbd_trigOutputEdge.dya = &m_attr_view->get_dim()->dynamic_attributes_manager().get_attribute(name);
			m_attr_view->write_dynamic_trigger_attribute_callback(cbd_trigOutputEdge);
		}


		INFO_STREAM << "Write tango attribute at Init - sensorCooling." << endl;
		Tango::WAttribute &sensorCooling = dev_attr->get_w_attr_by_name("sensorCooling");
		Tango::DevEnum val = 0;
		sensorCooling.set_write_value(val);
		yat4tango::DynamicAttributeWriteCallbackData cbd_sensorCooling;
		cbd_sensorCooling.tga = &sensorCooling;
		cbd_sensorCooling.dya = &m_attr_view->get_dim()->dynamic_attributes_manager().get_attribute("sensorCooling");
		m_attr_view->write_dynamic_cooling_attribute_callback(cbd_sensorCooling);


	}
	catch(Tango::DevFailed& df)
	{
		ERROR_STREAM << df << endl;
		return;
	}
	catch(lima::Exception& e)
	{
		ERROR_STREAM << "Initialization Failed : " << e.getErrMsg() << endl;
		return;
	}
}

/*----- PROTECTED REGION END -----*/	//	Dhyana6060::namespace_ending
} //	namespace
