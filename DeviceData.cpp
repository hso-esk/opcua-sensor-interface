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
 * \file    DeviceData.Cpp
 * \author  Institute of reliable Embedded Systems
 *          and Communication Electronics
 * \date    $Date$
 * \version $Version$
 *
 * \brief   Description of a single device data element.
 *
 *          A device consist of several device elements. A device data element
 *          for example can be a variable or value that can be read or written.
 */

/*
 * --- Includes ------------------------------------------------------------- *
 */
#include <DeviceData.h>
#include <stdint.h>
#include <iostream>
#include <string>



/*
 * --- Methods Definition ----------------------------------------------------- *
 */

/*---------------------------------------------------------------------------*/
/*
* getVal()
*/
const DeviceDataValue* DeviceData::getVal( void )
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
int16_t DeviceData::setVal( const DeviceDataValue* val )
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
int16_t DeviceData::observeVal( pf_observeCB pf_cb, void* p_param )
{
	if( m_observable )
	{
		if( pf_cb != NULL )
		{
			/* create a new callback elemet and insert it
			 * into the callback vector */
			struct s_cb cb =  { pf_cb, p_param };
			m_cbs.push_back( cb );
			m_observed = true;

			return 0;
		}
	}
	return -1;
}

/*---------------------------------------------------------------------------*/
/*
* observeVal()
*/
void DeviceData::valueChanged( const DeviceDataValue* val )
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



