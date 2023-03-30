/*----- PROTECTED REGION ID(TeledyneStateMachine.cpp) ENABLED START -----*/
//=============================================================================
//
// file :        TeledyneStateMachine.cpp
//
// description : State machine file for the Teledyne class
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

#include <Teledyne.h>

/*----- PROTECTED REGION END -----*/	//	Teledyne::TeledyneStateMachine.cpp

//================================================================
//  States   |  Description
//================================================================
//  FAULT    |  
//  INIT     |  
//  RUNNING  |  
//  STANDBY  |  


namespace Teledyne_ns
{
//=================================================
//		Attributes Allowed Methods
//=================================================

//--------------------------------------------------------
/**
 *	Method      : Teledyne::is_detector_model_allowed()
 *	Description : Execution allowed for detector_model attribute
 */
//--------------------------------------------------------
bool Teledyne::is_detector_model_allowed(TANGO_UNUSED(Tango::AttReqType type))
{

	//	Not any excluded states for detector_model attribute in read access.
	/*----- PROTECTED REGION ID(Teledyne::detector_modelStateAllowed_READ) ENABLED START -----*/
	
	/*----- PROTECTED REGION END -----*/	//	Teledyne::detector_modelStateAllowed_READ
	return true;
}

//--------------------------------------------------------
/**
 *	Method      : Teledyne::is_detector_type_allowed()
 *	Description : Execution allowed for detector_type attribute
 */
//--------------------------------------------------------
bool Teledyne::is_detector_type_allowed(TANGO_UNUSED(Tango::AttReqType type))
{

	//	Not any excluded states for detector_type attribute in read access.
	/*----- PROTECTED REGION ID(Teledyne::detector_typeStateAllowed_READ) ENABLED START -----*/
	
	/*----- PROTECTED REGION END -----*/	//	Teledyne::detector_typeStateAllowed_READ
	return true;
}

//--------------------------------------------------------
/**
 *	Method      : Teledyne::is_temperature_allowed()
 *	Description : Execution allowed for temperature attribute
 */
//--------------------------------------------------------
bool Teledyne::is_temperature_allowed(TANGO_UNUSED(Tango::AttReqType type))
{

	//	Not any excluded states for temperature attribute in read access.
	/*----- PROTECTED REGION ID(Teledyne::temperatureStateAllowed_READ) ENABLED START -----*/
	
	/*----- PROTECTED REGION END -----*/	//	Teledyne::temperatureStateAllowed_READ
	return true;
}

//--------------------------------------------------------
/**
 *	Method      : Teledyne::is_temperatureTarget_allowed()
 *	Description : Execution allowed for temperatureTarget attribute
 */
//--------------------------------------------------------
bool Teledyne::is_temperatureTarget_allowed(TANGO_UNUSED(Tango::AttReqType type))
{
	//	Not any excluded states for temperatureTarget attribute in Write access.
	/*----- PROTECTED REGION ID(Teledyne::temperatureTargetStateAllowed_WRITE) ENABLED START -----*/
	
	/*----- PROTECTED REGION END -----*/	//	Teledyne::temperatureTargetStateAllowed_WRITE

	//	Not any excluded states for temperatureTarget attribute in read access.
	/*----- PROTECTED REGION ID(Teledyne::temperatureTargetStateAllowed_READ) ENABLED START -----*/
	
	/*----- PROTECTED REGION END -----*/	//	Teledyne::temperatureTargetStateAllowed_READ
	return true;
}

//--------------------------------------------------------
/**
 *	Method      : Teledyne::is_gain_allowed()
 *	Description : Execution allowed for gain attribute
 */
//--------------------------------------------------------
bool Teledyne::is_gain_allowed(TANGO_UNUSED(Tango::AttReqType type))
{
	//	Not any excluded states for gain attribute in Write access.
	/*----- PROTECTED REGION ID(Teledyne::gainStateAllowed_WRITE) ENABLED START -----*/
	
	/*----- PROTECTED REGION END -----*/	//	Teledyne::gainStateAllowed_WRITE

	//	Not any excluded states for gain attribute in read access.
	/*----- PROTECTED REGION ID(Teledyne::gainStateAllowed_READ) ENABLED START -----*/
	
	/*----- PROTECTED REGION END -----*/	//	Teledyne::gainStateAllowed_READ
	return true;
}

//--------------------------------------------------------
/**
 *	Method      : Teledyne::is_adcRate_allowed()
 *	Description : Execution allowed for adcRate attribute
 */
//--------------------------------------------------------
bool Teledyne::is_adcRate_allowed(TANGO_UNUSED(Tango::AttReqType type))
{

	//	Not any excluded states for adcRate attribute in read access.
	/*----- PROTECTED REGION ID(Teledyne::adcRateStateAllowed_READ) ENABLED START -----*/
	
	/*----- PROTECTED REGION END -----*/	//	Teledyne::adcRateStateAllowed_READ
	return true;
}


//=================================================
//		Commands Allowed Methods
//=================================================


/*----- PROTECTED REGION ID(Teledyne::TeledyneStateAllowed.AdditionalMethods) ENABLED START -----*/

//	Additional Methods

/*----- PROTECTED REGION END -----*/	//	Teledyne::TeledyneStateAllowed.AdditionalMethods

}	//	End of namespace
