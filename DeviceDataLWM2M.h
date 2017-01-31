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

/**
 * \brief   LWM2M Sensor Class.
 *
 *          The LWM2M Sensor Class provides the
 */

class DeviceDataLWM2M
        : public DeviceData
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
                mp_lwm2mSrv = mp_lwm2mRes->getParent()->getParent()->getServer();
    };

    /**
     * \brief   Default Destructor of the sensor.
     *
     *          Since this is a pure virtual class acting as an interface
     *          this destructor should never be called directly.
     */
    virtual ~DeviceDataLWM2M( void ) {

        if( mp_lwm2mRes != NULL )
        {
            const LWM2MObject* p_obj = mp_lwm2mRes->getParent();
            if( p_obj != NULL )
                delete p_obj;
        }

    };

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

private:

    /** LWM2M Server this data was assigned to */
    LWM2MServer* mp_lwm2mSrv;

    /** LWM2M Resource this data was assigned to */
    LWM2MResource* mp_lwm2mRes;

};

#endif /* #ifndef __SENSORDATALWM2M_H__ */
