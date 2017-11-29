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

