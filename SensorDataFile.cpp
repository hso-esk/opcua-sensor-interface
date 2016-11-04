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
 * \file    SensorDataFile.cpp
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

/*
 * --- Includes ------------------------------------------------------------- *
 */
#include <iostream>
#include "SensorDataFile.h"


/*
 * --- Methods Definition ----------------------------------------------------- *
 */

/*---------------------------------------------------------------------------*/
/*
* getValNative()
*/
int16_t SensorDataFile::getValNative( SensorDataValue* val )
{
	/* Check for the file reference first */
	if( (m_file != NULL) && (val != 0) )
	{
		char buf[SENSORDATAVALUE_STRMAX];

		/* Seek to the value position which is the length of the description
		 * + its prefix + the newline at the end */
		if( fseek( m_file, strlen(SENSORDATAFILE_DESCR_PFX) + getDescr().length() + 1,
				SEEK_SET ) == 0 )
		{

			/* depending on the type read the value of the data */
			if( fgets( buf, SENSORDATAVALUE_STRMAX, m_file ) != NULL )
			{
				/* Data was read successfully. now put it to the
				 * according value buffer */
				switch( val->getType() )
				{
					case SensorDataValue::TYPE_INTEGER:
					{
						int32_t ibuf;
						sscanf( buf, "%d", &ibuf );
						return val->setVal( ibuf );
					}


					case SensorDataValue::TYPE_FLOAT:
					{
						float fbuf;
						sscanf( buf, "%f", &fbuf );
						return val->setVal( fbuf );
					}

					case SensorDataValue::TYPE_STRING:
						return val->setVal( buf );

					default:
						return -1;
				}
			}
			return -2;
		}
		return -3;
	}
	return -4;
}

/*---------------------------------------------------------------------------*/
/*
* setValNative()
*/
int16_t SensorDataFile::setValNative( SensorDataValue* val )
{
	/* Check for the file reference first */
	if( (m_file != NULL) && (val != 0) )
	{
		/* close the current file and reopen without default parameters */
		fclose(m_file);
		if( openFile( false ) == 0 )
		{
			/* Write the new data */
			switch( val->getType() )
			{
				case SensorDataValue::TYPE_INTEGER:
					fprintf( m_file, "%d\n", val->getVal().i32 );
					break;

				case SensorDataValue::TYPE_FLOAT:
					fprintf( m_file, "%f\n", val->getVal().f );
					break;

				case SensorDataValue::TYPE_STRING:
					fprintf( m_file, "%s\n", val->getVal().cStr );
					break;

				default:
					return -1;
			}
			return 0;
		}
		return -2;
	}
	return -3;
}

/*---------------------------------------------------------------------------*/
/*
* openFile()
*/
int16_t SensorDataFile::openFile( bool defaultVal )
{
	/* create access parameters */
	std::string fAccess = "";
	if( getWritable() )
		fAccess += "a+";
	else if( getReadable( ))
		fAccess += "r";

	fAccess += "b";

	/* create the file object according to the naming with
	 * full permission to create the file and to add the
	 * description and default value */
	m_file = fopen( getName().c_str(), "w" );

	if( m_file != NULL )
	{
		/* write the description of the value into the first line
		 * of the file. */
		fwrite( SENSORDATAFILE_DESCR_PFX, sizeof(char),
				strlen(SENSORDATAFILE_DESCR_PFX), m_file );
		fwrite( getDescr().c_str(), sizeof(char), getDescr().length(), m_file );
		fwrite( "\n", sizeof(char), 1, m_file );

		/* write default value if requested */
		if( defaultVal == true )
			fwrite( "0\n", sizeof(char), 2, m_file );
		fclose( m_file );

		/* create the file object according to the naming */
		m_file = fopen( getName().c_str(), fAccess.c_str() );
		if( m_file == NULL )
			return -1;
	}
	return 0;
}


