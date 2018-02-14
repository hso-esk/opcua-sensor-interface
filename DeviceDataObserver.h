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
 * \file    DeviceDataObserver.h
 * \author  Institute of reliable Embedded Systems
 *          and Communication Electronics
 * \date    $Date$
 * \version $Version$
 *
 * \brief   Definition of a Device Data Observer.
 *
 */


#ifndef __DEVICEDATAOBSERVER_H__
#define __DEVICEDATAOBSERVER_H__
#ifndef __DECL_DEVICEDATAOBSERVER_H__
#define __DECL_DEVICEDATAOBSERVER_H__ extern
#endif /* #ifndef __DECL_DEVICEDATAOBSERVER_H__ */


/*
 * --- Includes ------------------------------------------------------------- *
 */
#include <stdint.h>
#include <iostream>
#include <string>

#include "DeviceData.h"
#include "DeviceDataValue.h"

/*
 * --- Class Definition ----------------------------------------------------- *
 */

/**
 * \brief   DeviceDataObserver Class.
 *
 */
class DeviceDataObserver
{


public:


    /**
     * \brief   Default Constructor to create a observer element.
     */
    DeviceDataObserver( void ){};

    /**
     * \brief   Default Destructor of the observer element.
     */
    virtual ~DeviceDataObserver( void ) {};

    /**
     * \brief   Notify about the changes.
     *
     * \param   p_val   Value that changed.
     * \param   p_data  DeviceDataObject the change was reported from
     * \param   p_param User parameter.
     *
     */
    virtual int8_t notify( const DeviceDataValue* p_val,
        const DeviceData* p_data, void* p_param ) = 0;


};

#endif /* #ifndef __DEVICEDATAOBSERVER_H__ */

