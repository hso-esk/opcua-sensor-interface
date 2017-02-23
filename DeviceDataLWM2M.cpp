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
        const s_lwm2m_resobsparams_t* p_params )
{
    std::string dataStr = "";
    if( p_params->data != NULL )
    {
        dataStr.append( (char*)p_params->data, p_params->dataLength );

        /* set the new value and indicate change */
        DeviceDataValue val = *(getVal());
        val.setVal( (char*)dataStr.c_str() );

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
        (mp_lwm2mSrv->hasDevice( mp_lwm2mRes->getParent()->getParent()->getName() )))
    {
        std::string str;

        /* The Device with the according resource is available. So we can read
         * the value from the device. */
        ret = mp_lwm2mSrv->read( mp_lwm2mRes, str, NULL );

        if( ret == 0 )
        {
            /* read was successful. Now we can transfer the data to the according
             * value format. */
            /* Data was read successfully. now put it to the
             * according value buffer */
            switch( val->getType() )
            {
                case DeviceDataValue::TYPE_INTEGER:
                {
                    int32_t ibuf;
                    sscanf( str.c_str(), "%d", &ibuf );
                    ret = val->setVal( ibuf );
                    break;
                }

                case DeviceDataValue::TYPE_FLOAT:
                {
                    float fbuf;
                    sscanf( str.c_str(), "%f", &fbuf );
                    ret = val->setVal( fbuf );
                    break;
                }

                case DeviceDataValue::TYPE_STRING:
                    ret = val->setVal( str.c_str() );
                    break;

                default:
                    ret = -1;
                    break;
            }
        }
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
        (mp_lwm2mSrv->hasDevice( mp_lwm2mRes->getParent()->getParent()->getName() )))
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
int8_t DeviceDataLWM2M::observeValNative( void )
{
    int8_t ret = -1;

    if( (mp_lwm2mSrv != NULL) &&
        (mp_lwm2mSrv->hasDevice( mp_lwm2mRes->getParent()->getParent()->getName() )))
    {
      /* observe the value */
      if( mp_lwm2mSrv->observe( mp_lwm2mRes, true, &m_cbData ) == 0 )
      {
        /* observe was successful */
        ret = mp_lwm2mRes->registerObserver( this );
      }
    }
    return ret;
}

