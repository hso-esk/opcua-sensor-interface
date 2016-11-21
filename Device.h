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
 * \file    Device.h
 * \author  Institute of reliable Embedded Systems
 *          and Communication Electronics
 * \date    $Date$
 * \version $Version$
 *
 * \brief   Description of the general Device Interface.
 *
 *          The general Device Interface shall be used as base class for all
 *          kind of specific devices.
 */


#ifndef __DEVICE_H__
#define __DEVICE_H__
#ifndef __DECL_DEVICE_H__
#define __DECL_DEVICE_H__ extern
#endif /* #ifndef __DECL_DEVICE_H__ */


/*
 * --- Includes ------------------------------------------------------------- *
 */
#include <stdint.h>
#include <iostream>
#include <string>

/*
 * --- Class Definition ----------------------------------------------------- *
 */

/**
 * \brief   General Device Class.
 *
 *          The Device Class provides the base class for all devices.
 */
class Device
{

public:

    /**
     * \brief   Default Constructor to create a device.
     */
    Device();

    /**
     * \brief   Constructor to create a device with a specific name.
     *
     *          This constructor can be used to create a device with
     *          a specific name.
     */
    Device( std::string name );

    /**
     * \brief   Default Destructor of the device.
     */
	virtual ~Device();

    /**
     * \brief   Get the name of the device.
     *
     * \return  The name of the device.
     */
    std::string getName( void );

    /**
     * \brief   Set the name of the device.
     *
     * \param   name    Name to give to the device.
     */
    void setName( std::string name );

private:

    /** name of the device */
    std::string m_name;
	
};

#endif /* #ifndef __DEVICE_H__ */

