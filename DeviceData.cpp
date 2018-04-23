/*
 * --- License -------------------------------------------------------------- *
 */

/*
 * Copyright 2017 NIKI 4.0 project team
 *
 * NIKI 4.0 was financed by the Baden-Württemberg Stiftung gGmbH (www.bwstiftung.de).
 * Project partners are FZI Forschungszentrum Informatik am Karlsruher
 * Institut für Technologie (www.fzi.de), Hahn-Schickard-Gesellschaft
 * für angewandte Forschung e.V. (www.hahn-schickard.de) and
 * Hochschule Offenburg (www.hs-offenburg.de).
 * This file was developed by the Institute of reliable Embedded Systems
 * and Communication Electronics
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
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
#include "DeviceData.h"
#include "DeviceDataObserver.h"
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
int16_t DeviceData::observeVal( DeviceDataObserver* p_obs, void* p_param,bool direct )
{
    if( m_observable )
    {
        if( p_obs != NULL )
        {
            /* call native observe */
            if( observeValNative( direct ) == 0 )
            {
              /* create a new callback elemet and insert it
               * into the callback vector */
              struct s_obs obs =  { p_obs, p_param };
              m_obs.push_back( obs );

              m_observed = true;
              return 0;
            }
            else
              /* Observe was not successful so reset the flag */
              m_observed = false;
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
    if(val != NULL)
    {
        /* update value */
        m_val = *val;

        /* check the callback vector and inform all
         * observers */
        std::vector< s_obs >::iterator it;;

        for (it = m_obs.begin() ; it != m_obs.end(); ++it)
        {
            /* call the current callback function */
            if( (it->p_obs != NULL) )
                it->p_obs->notify( &m_val, this, it->p_param );
        }
    }
}

