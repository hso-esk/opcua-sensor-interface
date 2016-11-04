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
	int16_t ret = -1;
	FILE* p_file = openFile();

	/* Check for the file reference first */
	if( (p_file != NULL) && (val != 0) )
	{
		char buf[SENSORDATAVALUE_STRMAX];

		/* Seek to the value position which is the length of the description
		 * + its prefix + the newline at the end */
		if( fseek( p_file, strlen(SENSORDATAFILE_DESCR_PFX) + getDescr().length() + 1,
				SEEK_SET ) == 0 )
		{

			/* depending on the type read the value of the data */
			if( fgets( buf, SENSORDATAVALUE_STRMAX, p_file ) != NULL )
			{
				/* Data was read successfully. now put it to the
				 * according value buffer */
				switch( val->getType() )
				{
					case SensorDataValue::TYPE_INTEGER:
					{
						int32_t ibuf;
						sscanf( buf, "%d", &ibuf );
						ret = val->setVal( ibuf );
						break;
					}


					case SensorDataValue::TYPE_FLOAT:
					{
						float fbuf;
						sscanf( buf, "%f", &fbuf );
						ret = val->setVal( fbuf );
						break;
					}

					case SensorDataValue::TYPE_STRING:
						ret = val->setVal( buf );
						break;

					default:
						ret = -1;
						break;
				}
			}
			else
				ret = -2;
		}
		else
			ret = -3;
		fclose( p_file );
	}
	else
		ret = -4;

	return ret;
}

/*---------------------------------------------------------------------------*/
/*
* setValNative()
*/
int16_t SensorDataFile::setValNative( const SensorDataValue* val )
{
	int16_t ret = -1;
	FILE* p_file = openFile( true );

	/* Check for the file reference first */
	if( (p_file != NULL) && (val != 0) )
	{
		/* Write the new data */
		switch( val->getType() )
		{
			case SensorDataValue::TYPE_INTEGER:
				fprintf( p_file, "%d\n", val->getVal().i32 );
				ret = 0;
				break;

			case SensorDataValue::TYPE_FLOAT:
				fprintf( p_file, "%g\n", val->getVal().f );
				ret = 0;
				break;

			case SensorDataValue::TYPE_STRING:
				fprintf( p_file, "%s\n", val->getVal().cStr );
				ret = 0;
				break;

			default:
				ret = -1;
				break;
		}
		fclose( p_file );
	}
	else
		ret = -1;

	return ret;
}

/*---------------------------------------------------------------------------*/
/*
* openFile()
*/
FILE* SensorDataFile::openFile( bool wr, bool defaultVal )
{
	FILE* p_ret = NULL;

	/* create access parameters */
	std::string fAccess = "";
	if( getWritable() && (wr == true) )
		fAccess += "a+";
	else if( getReadable( ))
		fAccess += "r";

	fAccess += "b";

	if( wr == true )
	{
		/* create the file object according to the naming with
		 * full permission to create the file and to add the
		 * description and default value */
		p_ret = fopen( getName().c_str(), "w" );

		if( (p_ret != NULL)  )
		{
			/* write the description of the value into the first line
			 * of the file. */
			fwrite( SENSORDATAFILE_DESCR_PFX, sizeof(char),
					strlen(SENSORDATAFILE_DESCR_PFX), p_ret );
			fwrite( getDescr().c_str(), sizeof(char), getDescr().length(), p_ret );
			fwrite( "\n", sizeof(char), 1, p_ret );

			/* write default value if requested */
			if( defaultVal == true )
				fwrite( "0\n", sizeof(char), 2, p_ret );
			fclose( p_ret );
		}
	}

	/* create the file object according to the naming */
	p_ret = fopen( getName().c_str(), fAccess.c_str() );
	return p_ret;
}


