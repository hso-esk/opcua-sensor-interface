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
 * \file    SensorDataFile.h
 * \author  Institute of reliable Embedded Systems
 *          and Communication Electronics
 * \date    $Date$
 * \version $Version$
 *
 * \brief   Description of the file sensor data element.
 *
 *          The file sensor data element describes a specific sensor data
 *          that is accessible using the file system. Therefore it inherits
 *          from the general sensor data interface and includes some additional
 *          functions e.g. to access the according file descriptors.
 */
#ifndef __SENSORDATAFILE_H__
#define __SENSORDATAFILE_H__
#ifndef __DECL_SENSORDATAFILE_H__
#define __DECL_SENSORDATAFILE_H__ extern
#endif /* #ifndef __DECL_SENSORDATAFILE_H__ */


/*
 * --- Includes ------------------------------------------------------------- *
 */
#include <iostream>
#include "SensorData.h"

/*
 * --- DEFINES -------------------------------------------------------------- *
 */

/** Prefix of the description line */
#define SENSORDATAFILE_DESCR_PFX			"# "


/*
 * --- Class Definition ----------------------------------------------------- *
 */

/**
 * \brief   File Sensor Class.
 *
 *          The File Sensor Class provides the
 */
class SensorDataFile
		: public SensorData
{

public:

    /**
     * \brief   Default Constructor to create a sensor.
     *
     */
	SensorDataFile( void )
		: SensorData()
		, m_file( NULL) {};


    /**
     * \brief   Constructor with a specific default name and description.
     *
     * \param   name    Name of the sensor data element.
     * \param   descr   Description of the sensor data element.
     * \param	val		Value of the data.
     */
	SensorDataFile( std::string name, std::string descr, SensorDataValue::e_type type,
			int access )
		: SensorData( name, descr, type, access )
		, m_file(NULL) {

		/* open the file */
		openFile( true );
	};

    /**
     * \brief   Default Destructor of the sensor.
     *
     *          Since this is a pure virtual class acting as an interface
     *          this destructor should never be called directly.
     */
	virtual ~SensorDataFile( void ) {
		if( m_file != NULL )
		{
			/* close file */
			fclose(m_file);
			m_file = NULL;
		}

		/* delete file from system */
		remove( getName().c_str() );
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
    virtual int16_t getValNative( SensorDataValue* val );

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
    virtual int16_t setValNative( SensorDataValue* val );

    /**
     * \brief	Opens the internal file descriptor.
     *
     * \param	defaultVal	Write default vavlue or not.
     * \return 	0 on success.
     */
    int16_t openFile( bool defaultVal = false );

private:

    /** file object */
    FILE* m_file;
	
};

#endif /* #ifndef __SENSORDATAFILE_H__ */
