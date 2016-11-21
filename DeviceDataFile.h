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
#include <DeviceData.h>

/*
 * --- DEFINES -------------------------------------------------------------- *
 */

/** Prefix of the description line */
#define DEVICEDATAFILE_DESCR_PFX			"# "


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
     * \param	val		Value of the data.
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
     * \brief	Opens the internal file descriptor.
     *
     * \param	wr			Open for writing or not.
     * \param	defaultVal	Write default value or not.
     *
     * \return 	File Pointer on success or NULL on failure.
     */
    FILE* openFile( bool wr = false, bool defaultVal = false );

private:
	
};

#endif /* #ifndef __DEVICEDATAFILE_H__ */
