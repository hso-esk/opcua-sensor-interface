/*
 * --- License -------------------------------------------------------------- *
 */

/*
 * Copyright (c) 2015
 *
 * Hochschule Offenburg, University of Applied Sciences
 * Institute for reliable Embedded Systems
 * and Communications Electronic (ivESK)
 *
 * All rights reserved
*/

/*
 * --- Module Description --------------------------------------------------- *
 */

/**
 * \file    SensorData.Cpp
 * \author  Institute of reliable Embedded Systems
 *          and Communication Electronics
 * \date    $Date$
 * \version $Version$
 *
 * \brief   Description of a single sensor data element.
 *
 *          A sensor consist of several sensor elements. A sensor data element
 *          for example can be a variable or value that can be read or written.
 */

/*
 * --- Includes ------------------------------------------------------------- *
 */
#include <stdint.h>
#include <iostream>
#include <string>

#include "SensorData.h"


/*
 * --- Methods Definition ----------------------------------------------------- *
 */

/*---------------------------------------------------------------------------*/
/*
* getVal()
*/
const SensorDataValue* SensorData::getVal( void )
{
	/* check if the value is readable */
	if( m_readable)
	{
		if( m_observed == false )
		{
			/* Value is readable. Call the native function
			 * to access the value. */
			if( getValNative( &m_val ) != 0 )
				/* invalid value */
				return NULL;
		}
		return &m_val;
	}
	return NULL;
}

/*---------------------------------------------------------------------------*/
/*
* setVal()
*/
int16_t SensorData::setVal( const SensorDataValue* val )
{
	/* check if the value is writable */
	if( m_writable)
	{
		/* Value is writable. Call the native function
		 * to access the value. */
		if( setValNative( val ) == 0 )
		{
			/* value was set properly, issue callbacks */
			valueChanged( val );
			return 0;
		}
		return -2;
	}
	return -1;

}

/*---------------------------------------------------------------------------*/
/*
* observeVal()
*/
int16_t SensorData::observeVal( pf_observeCB pf_cb, void* p_param )
{
	if( pf_cb != NULL )
	{
		/* create a new callback elemet and insert it
		 * into the callback vector */
		struct s_cb cb =  { pf_cb, p_param };
		m_cbs.push_back( cb );
		return 0;
	}

	return -1;
}

/*---------------------------------------------------------------------------*/
/*
* observeVal()
*/
void SensorData::valueChanged( const SensorDataValue* val )
{
	if( (val != NULL) && (*val != m_val) )
	{
		/* update value */
		m_val = *val;

		/* check the callback vector and inform all
		 * observers */
		std::vector< s_cb >::iterator it;;

		for (it = m_cbs.begin() ; it != m_cbs.end(); ++it)
		{
			/* call the current callback function */
			if( (it->pf_cb != NULL) )
				it->pf_cb( &m_val, it->p_param );
		}
	}
}



