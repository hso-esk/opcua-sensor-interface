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
 * \file    DeviceDataFile.h
 * \author  Institute of reliable Embedded Systems
 *          and Communication Electronics
 * \date    $Date$
 * \version $Version$
 *
 * \brief   Description of the file device data element.
 *
 *          The file device data element describes a specific device data
 *          that is accessible using the file system. Therefore it inherits
 *          from the general device data interface and includes some additional
 *          functions e.g. to access the according file descriptors.
 */
#ifndef __DEVICEDATAFILE_H__
#define __DEVICEDATAFILE_H__

#ifndef __DECL_DEVICEDATAFILE_H__
#define __DECL_DEVICEDATAFILE_H__ extern
#endif /* #ifndef __DECL_DEVICEDATAFILE_H__ */


/*
 * --- Includes ------------------------------------------------------------- *
 */
#include <iostream>
#include "DeviceData.h"

/*
 * --- DEFINES -------------------------------------------------------------- *
 */

/** Prefix of the description line */
#define DEVICEDATAFILE_DESCR_PFX            "# "


/*
 * --- Class Definition ----------------------------------------------------- *
 */

/**
 * \brief   File Device Class.
 *
 *          The File Device Class provides the
 */
class DeviceDataFile
        : public DeviceData
{

public:

    /**
     * \brief   Default Constructor to create a device.
     *
     */
    DeviceDataFile( void )
        : DeviceData() {

        /* open the file */
        FILE* p_file = openFile( true, true );
        if( p_file != NULL )
            fclose(p_file);
    };


    /**
     * \brief   Constructor with a specific default name and description.
     *
     * \param   name    Name of the device data element.
     * \param   descr   Description of the device data element.
     * \param    type    Type of the data value.
     * \param    access    Access permissions.
     */
    DeviceDataFile( std::string name, std::string descr, DeviceDataValue::e_type type,
            int access )
        : DeviceData( name, descr, type, access ) {

        /* open the file */
        FILE* p_file = openFile( true, true );
        if( p_file != NULL )
            fclose(p_file);
    };

    /**
     * \brief   Default Destructor of the device.
     *
     *          Since this is a pure virtual class acting as an interface
     *          this destructor should never be called directly.
     */
    virtual ~DeviceDataFile( void ) {
        /* delete file from system */
        remove( getName().c_str() );
    };


private:

    /**
     * \brief   Native read function to get the device data value.
     *
     *          A device can be accessed using different types of mechanisms
     *          or protocols (e.g. ProfiBus, LWM2M). Therefore, the native
     *          read function is the interface from the abstract device data
     *          description and the actual protocol dependent implementation.
     *          Each device type has to implement this function accordingly.
     *
     * \return  0 on success.
     */
    virtual int16_t getValNative( DeviceDataValue* val );

    /**
     * \brief   Native write function to get the device data value.
     *
     *          A device can be accessed using different types of mechanisms
     *          or protocols (e.g. ProfiBus, LWM2M). Therefore, the native
     *          write function is the interface from the abstract device data
     *          description and the actual protocol dependent implementation.
     *          Each device type has to implement this function accordingly.
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
     * \return  0 on success.
     */
    virtual int8_t observeValNative( void );

    /**
     * \brief    Opens the internal file descriptor.
     *
     * \param    wr            Open for writing or not.
     * \param    defaultVal    Write default value or not.
     *
     * \return     File Pointer on success or NULL on failure.
     */
    FILE* openFile( bool wr = false, bool defaultVal = false );

private:

};

#endif /* #ifndef __DEVICEDATAFILE_H__ */
