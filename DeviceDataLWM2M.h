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
#ifndef __SENSORDATALWM2M_H__
#define __SENSORDATALWM2M_H__

#ifndef __DECL_SENSORDATALWM2M_H__
#define __DECL_SENSORDATALWM2M_H__ extern
#endif /* #ifndef __DECL_SENSORDATALWM2M_H__ */


/*
 * --- Includes ------------------------------------------------------------- *
 */
#include <iostream>

#include "DeviceData.h"
#include "LWM2MServer.h"
#include "LWM2MDevice.h"
#include "LWM2MObject.h"
#include "LWM2MResource.h"
#include "LWM2MResourceObserver.h"

/**
 * \brief   LWM2M Sensor Class.
 *
 *          The LWM2M Sensor Class provides the
 */

class DeviceDataLWM2M
        : public DeviceData
        , public LWM2MResourceObserver
{

public:

    /**
     * \brief   Default Constructor to create a sensor.
     *
     */
    DeviceDataLWM2M( void )
        : DeviceData()
        , mp_lwm2mSrv( NULL )
        , mp_lwm2mRes( NULL ) {};


    /**
     * \brief   Constructor with a specific default name and description.
     *
     * \param   name        Name of the sensor data element.
     * \param   descr       Description of the sensor data element.
     * \param    val            Value of the data.
     * \param    p_lwm2mRes    LWM2M Resource the data resource to.
     */
    DeviceDataLWM2M( std::string name, std::string descr, DeviceDataValue::e_type type,
            int access, LWM2MResource* p_lwm2mRes )
        : DeviceData( name, descr, type, access )
        , mp_lwm2mSrv( NULL )
        , mp_lwm2mRes( p_lwm2mRes ){

            if( mp_lwm2mRes != NULL )
                mp_lwm2mSrv = mp_lwm2mRes->getServer();
    };


    /**
     * \brief   Default Destructor of the sensor.
     *
     *          Since this is a pure virtual class acting as an interface
     *          this destructor should never be called directly.
     */
    virtual ~DeviceDataLWM2M( void ) {};


    /**
     * \brief   Return the LWM2MRessource mapped to the data..
     *
     * \return  The LWM2M Resource mapped to the Data.
     */
    LWM2MResource* getResource( void ) const { return mp_lwm2mRes; };

    /**
     * \brief    Get the resource ID.
     *
     * \param    p_srv        The server the notification is from.
     * \param    p_res        The resource the notification is for.
     * \param    p_params    Parameters of the notification.
     *
     * \return     0 on success or negative value on error.
     */
    virtual int8_t notify( const LWM2MServer* p_srv, const LWM2MResource* p_res,
            const s_lwm2m_obsparams_t* p_params );

private:

    /**
     * \brief   Native read function to get the sensor data value.
     *
     *          A sensor can be accessed using different types of mechanisms
     *          or protocols (e.g. ProfiBus, LWM2M). Therefore, the native
     *          read function is the interface from the abstract sensor data
     *          description and the actual protocol dependent implementation.
     *          Each sensor type has to implement this function accordingly.
     *
     * \return  0 on success.
     */
    virtual int16_t getValNative( DeviceDataValue* val );

    /**
     * \brief   Native write function to get the sensor data value.
     *
     *          A sensor can be accessed using different types of mechanisms
     *          or protocols (e.g. ProfiBus, LWM2M). Therefore, the native
     *          write function is the interface from the abstract sensor data
     *          description and the actual protocol dependent implementation.
     *          Each sensor type has to implement this function accordingly.
     *
     * \return  0 on success.
     */
    virtual int16_t setValNative( const DeviceDataValue* val );

    /**
     * \brief   Native function to observe the device data value.
     *
     *          A device can be accessed using different types of mechanisms
     *          or protocols (e.g. ProfiBus, LWM2M). Therefore, the observe
     *           function is the interface from the abstract device data
     *          description and the actual protocol dependent implementation.
     *          Each device type has to implement this function accordingly.
     *
     * \param   direct  Direct Observation or observed by higher instance.
     *
     * \return  0 on success.
     */
    virtual int8_t observeValNative( bool direct = true );

private:

    /** LWM2M Server this data was assigned to */
    LWM2MServer* mp_lwm2mSrv;

    /** LWM2M Resource this data was assigned to */
    LWM2MResource* mp_lwm2mRes;
};

#endif /* #ifndef __SENSORDATALWM2M_H__ */
