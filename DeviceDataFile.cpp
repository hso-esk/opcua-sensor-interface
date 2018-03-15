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
 * \file    DeviceDataFile.cpp
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

/*
 * --- Includes ------------------------------------------------------------- *
 */
#include "DeviceDataFile.h"
#include <iostream>


/*
 * --- Methods Definition ----------------------------------------------------- *
 */

/*---------------------------------------------------------------------------*/
/*
* getValNative()
*/
int16_t DeviceDataFile::getValNative( DeviceDataValue* val )
{
    int16_t ret = -1;
    FILE* p_file = openFile();

    /* Check for the file reference first */
    if( (p_file != NULL) && (val != 0) )
    {
        char buf[DEVICEDATAVALUE_STRMAX];

        /* Seek to the value position which is the length of the description
         * + its prefix + the newline at the end */
        if( fseek( p_file, strlen(DEVICEDATAFILE_DESCR_PFX) + getDescr().length() + 1,
                SEEK_SET ) == 0 )
        {

            /* depending on the type read the value of the data */
            if( fgets( buf, DEVICEDATAVALUE_STRMAX, p_file ) != NULL )
            {
                /* Data was read successfully. now put it to the
                 * according value buffer */
                switch( val->getType() )
                {
                    case DeviceDataValue::TYPE_INTEGER:
                    {
                        int32_t ibuf;
                        sscanf( buf, "%d", &ibuf );
                        ret = val->setVal( ibuf );
                        break;
                    }


                    case DeviceDataValue::TYPE_FLOAT:
                    {
                        float fbuf;
                        sscanf( buf, "%f", &fbuf );
                        ret = val->setVal( fbuf );
                        break;
                    }

                    case DeviceDataValue::TYPE_STRING:
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
int16_t DeviceDataFile::setValNative( const DeviceDataValue* val )
{
    int16_t ret = -1;
    FILE* p_file = openFile( true );

    /* Check for the file reference first */
    if( (p_file != NULL) && (val != 0) )
    {
        /* Write the new data */
        switch( val->getType() )
        {
            case DeviceDataValue::TYPE_INTEGER:
                fprintf( p_file, "%d\n", val->getVal().i32 );
                ret = 0;
                break;

            case DeviceDataValue::TYPE_FLOAT:
                fprintf( p_file, "%g\n", val->getVal().f );
                ret = 0;
                break;

            case DeviceDataValue::TYPE_STRING:
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
* observeValNative()
*/
int8_t DeviceDataFile::observeValNative( bool direct )
{
    int8_t ret = 0;
    return ret;
}

/*---------------------------------------------------------------------------*/
/*
* openFile()
*/
FILE* DeviceDataFile::openFile( bool wr, bool defaultVal )
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
            fwrite( DEVICEDATAFILE_DESCR_PFX, sizeof(char),
                    strlen(DEVICEDATAFILE_DESCR_PFX), p_ret );
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


