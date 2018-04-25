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
 * \file    DeviceDataLWM2M.h
 * \author  Institute of reliable Embedded Systems
 *          and Communication Electronics
 * \date    $Date$
 * \version $Version$
 *
 * \brief   Description of the LWM2M sensor data element.
 *
 *          The LWM2M Sensor data element describes a specific sensor data
 *          that is accessible using the LWM2M protocol. Therefore it inherits
 *          from the general sensor data interface and includes some additional
 *          functions e.g. to access the according LMWM2M device.
 */

/*
 * --- Includes ------------------------------------------------------------- *
 */
#include <DeviceDataLWM2M.h>
#include <iostream>



/*
 * --- Methods Definition ----------------------------------------------------- *
 */


/*---------------------------------------------------------------------------*/
/*
* getValNative()
*/
int8_t DeviceDataLWM2M::notify( const LWM2MServer* p_srv,  const LWM2MResource* p_res,
        const s_lwm2m_obsparams_t* p_params )
{
    std::string dataStr = "";

    if( (p_params != NULL) && (p_params->data != NULL) )
    {
        DeviceDataValue val = *(getVal());
        switch( p_params->data->type )
        {
          case LWM2M_TYPE_STRING:
            dataStr.append( (char*)p_params->data->value.asBuffer.buffer );
            val.setVal( (char*)dataStr.c_str() );
            break;

          case LWM2M_TYPE_INTEGER:
          case LWM2M_TYPE_BOOLEAN:
            val.setVal( (int)p_params->data->value.asInteger );
            break;

          case LWM2M_TYPE_FLOAT:
            val.setVal( (float)p_params->data->value.asFloat );
            break;

          case LWM2M_TYPE_OPAQUE:
            val.setVal( p_params->data->value.asBuffer.buffer,
                p_params->data->value.asBuffer.length );
            break;

          default:
            break;
        }

        valueChanged( &val );
    }

    return 0;
}

/*---------------------------------------------------------------------------*/
/*
* getValNative()
*/
int16_t DeviceDataLWM2M::getValNative( DeviceDataValue* val )
{
    int16_t ret = -1;

    if( (mp_lwm2mSrv != NULL) &&
        (mp_lwm2mSrv->hasDevice( mp_lwm2mRes->getDevice()->getName() )))
    {
        lwm2m_data_t* data;
        std::string dataStr = "";

        /* The Device with the according resource is available. So we can read
         * the value from the device. */
        ret = mp_lwm2mSrv->read( mp_lwm2mRes, &data, NULL );

        if( (val != NULL) && (data != NULL) && (ret > 0) )
        {
            switch( data->type )
            {
                case LWM2M_TYPE_STRING:
                    dataStr.assign( (char*)data->value.asBuffer.buffer,
                        data->value.asBuffer.length );
                    val->setVal( (char*)dataStr.c_str() );
                    break;

                case LWM2M_TYPE_INTEGER:
                case LWM2M_TYPE_BOOLEAN:
                    val->setVal( (int)data->value.asInteger );
                    break;

                case LWM2M_TYPE_FLOAT:
                    val->setVal( (float)data->value.asFloat );
                    break;

                case LWM2M_TYPE_OPAQUE:
                  val->setVal( data->value.asBuffer.buffer,
                      data->value.asBuffer.length );
                  break;

                default:
                    break;
            }
            ret = 0;
        }

        if( (data != NULL) && (ret > 0) )
          lwm2m_data_free( ret, data );
    }
    return ret;
}

/*---------------------------------------------------------------------------*/
/*
* setValNative()
*/
int16_t DeviceDataLWM2M::setValNative( const DeviceDataValue* val )
{
    int16_t ret = -1;
    char buf[100];

    if( (mp_lwm2mSrv != NULL) &&
        (mp_lwm2mSrv->hasDevice( mp_lwm2mRes->getDevice()->getName() )))
    {
        /* Write the new data */
        switch( val->getType() )
        {
            case DeviceDataValue::TYPE_INTEGER:
                snprintf( buf, 100, "%d", val->getVal().i32 );
                ret = 0;
                break;

            case DeviceDataValue::TYPE_FLOAT:
                snprintf( buf, 100, "%f", val->getVal().f );
                ret = 0;
                break;

            case DeviceDataValue::TYPE_STRING:
                snprintf( buf, 100, "%s", val->getVal().cStr );
                ret = 0;
                break;

            default:
                ret = -1;
                break;
        }

        if( ret == 0 )
        {
            /* write the data via LWM2M */
            ret = mp_lwm2mSrv->write( mp_lwm2mRes, buf, NULL );
        }
    }
    return ret;
}

/*---------------------------------------------------------------------------*/
/*
* observeValNative()
*/
int8_t DeviceDataLWM2M::observeValNative( bool direct )
{
    int8_t ret = -1;

    if( (mp_lwm2mSrv != NULL) &&
        (mp_lwm2mSrv->hasDevice( mp_lwm2mRes->getDevice()->getName() )))
    {

      /* register observer in advance */
      ret = mp_lwm2mRes->registerObserver( this );

      if( (ret == 0) && (m_observed == false))
      {
        m_observed = true;

        if( direct )
          /* observe the value */
          ret = mp_lwm2mSrv->observe( mp_lwm2mRes, true );

        if( ret != 0 )
        {
          /* observe was not successful */
          ret = mp_lwm2mRes->deregisterObserver( this );
          ret = -1;
        }
      }
    }
    return ret;
}

