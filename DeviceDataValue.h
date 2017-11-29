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
 * \file    DeviceDataValue.h
 * \author  Institute of reliable Embedded Systems
 *          and Communication Electronics
 * \date    $Date$
 * \version $Version$
 *
 * \brief   Description of a single device data value element.
 *
 *          A device data value element holds the actual data with a specific
 *          type such as integer float or string.
 */


#ifndef __DEVICEDATAVALUE_H__
#define __DEVICEDATAVALUE_H__
#ifndef __DECL_DEVICEDATAVALUE_H__
#define __DECL_DEVICEDATAVALUE_H__ extern
#endif /* #ifndef __DECL_DEVICEDATAVALUE_H__ */


/*
 * --- Includes ------------------------------------------------------------- *
 */
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <iostream>
#include <string>
#include <arpa/inet.h>

/*
 * --- DEFINES -------------------------------------------------------------- *
 */

/** maximum length of the value as a string */
#define DEVICEDATAVALUE_STRMAX            50
#define DEVICEDATAVALUE_OPAQUEMAX         50

/*
 * --- Class Definition ----------------------------------------------------- *
 */
class DeviceDataValue
{
public:

    /** Enumeration for the different types of the value */
    enum e_type
    {
        /** integer type */
        TYPE_INTEGER,
        /** float type */
        TYPE_FLOAT,
        /** string type */
        TYPE_STRING,
        /** Opaque type */
        TYPE_OPAQUE
    };

    /** union of the value */
    union u_val
    {
        /** value as integer */
        int32_t i32;
        /** value as float */
        float f;
        /** value as string */
        char cStr[DEVICEDATAVALUE_STRMAX];

        union
        {
          /** value */
          uint8_t val[DEVICEDATAVALUE_OPAQUEMAX];
          /** length */
          uint16_t len;
        } u_opaque;
    };

    /** overloaded comparison operator */
    friend bool operator== (const DeviceDataValue& cmp1,
            const DeviceDataValue& cmp2) {

        if( cmp1.m_type != cmp2.m_type )
            return false;

        switch( cmp1.m_type )
        {
            case TYPE_INTEGER:
                if( cmp1.m_val.i32 != cmp2.m_val.i32 )
                    return false;
                break;

            case TYPE_FLOAT:
                if( cmp1.m_val.f != cmp2.m_val.f )
                    return false;
                break;

            case TYPE_STRING:
                if( strlen(cmp1.m_val.cStr) != strlen(cmp2.m_val.cStr) )
                    return false;
                if(strcmp(cmp1.m_val.cStr, cmp2.m_val.cStr) != 0)
                    return false;
                break;

            case TYPE_OPAQUE:
                if( cmp1.m_val.u_opaque.len != cmp2.m_val.u_opaque.len )
                    return false;
                if( memcmp( cmp1.m_val.u_opaque.val, cmp2.m_val.u_opaque.val,
                    cmp1.m_val.u_opaque.len ) != 0)
                  return false;
                break;

            default:
                return false;
        }

        return true;
    }

    /** overloaded comparison operator */
    friend bool operator!= (const DeviceDataValue& cmp1,
            const DeviceDataValue& cmp2) {
        return ! (cmp1 == cmp2);
    }

    /**
     * \brief   Constructor with a specific default type.
     *
     * \param   type    Type of the value.
     */
    DeviceDataValue( DeviceDataValue::e_type type )
        : m_type( type ) {

        /* reset members */
        memset( &m_val, 0, sizeof(m_val) );
    };

    /**
     * \brief   Default destructor.
     */
    virtual ~DeviceDataValue( void ) {};

    /**
     * \brief    Get the type of the value,
     *
     *     \return Type of the value
     */
    int16_t getType( void ) const {return m_type;}

    /**
     * \brief    Get the actual value,
     *
     *     \return The actual value
     */
    u_val getVal( void ) const {return m_val;}

    /**
     * \brief    Set the value of the data value element as integer,
     *
     *             Sets the value of the data element as as integer. If
     *             the types do not match the value will not be assigned.
     *
     *     \param    val        Value to set.
     *
     *     \return 0 on success.
     */
    int16_t setVal( int32_t val ) {
        if( m_type == TYPE_INTEGER )
        {
            m_val.i32 = val;
            return 0;
        }
        else if( m_type == TYPE_FLOAT )
        {
            m_val.f = (float)val;
            return 0;
        }
        else if( m_type == TYPE_STRING )
        {
          snprintf(m_val.cStr, DEVICEDATAVALUE_STRMAX,
                  "%d", val );
          return 0;
        }
        else if ( m_type == TYPE_OPAQUE )
        {
          return -1;
        }
        return -1;
    }

    /**
     * \brief    Set the value of the data value element as float,
     *
     *             Sets the value of the data element as as float. If
     *             the types do not match the value will not be assigned.
     *
     *     \param    val        Value to set.
     *
     *     \return 0 on success.
     */
    int16_t setVal( float val ) {
        if( m_type == TYPE_FLOAT )
        {
            m_val.f = val;
            return 0;
        }
        else if( m_type == TYPE_INTEGER )
        {
          m_val.i32 = (int32_t)val;
          return 0;
        }
        else if( m_type == TYPE_STRING )
        {
          snprintf(m_val.cStr, DEVICEDATAVALUE_STRMAX,
                  "%f", val );
          return 0;
        }
        else if ( m_type == TYPE_OPAQUE )
        {
          return -1;
        }
        return -1;
    }

    /**
     * \brief    Set the value of the data value element as string,
     *
     *             Sets the value of the data element as as string.
     *             CR and LF will be ignored and act as a stop
     *             condition. If the types do not match the value will not
     *             be assigned.
     *
     *     \param    val        Value to set.
     *
     *     \return 0 on success.
     */
    int16_t setVal( std::string val ) {
        if( m_type == TYPE_STRING )
        {
            size_t l = snprintf(m_val.cStr, DEVICEDATAVALUE_STRMAX,
                    "%s", val.c_str());
            size_t pos = strcspn( m_val.cStr, "\r\n" );

            /* remove trailing CR or LF if it exists */
            if( pos  < l )
                m_val.cStr[pos] = '\0';
            return 0;
        }
        else if( m_type == TYPE_INTEGER )
        {
          sscanf( val.c_str(), "%d", &m_val.i32 );
          return 0;
        }
        else if( m_type == TYPE_FLOAT )
        {
          sscanf( val.c_str(), "%f", &m_val.f );
          return 0;
        }
        else if ( m_type == TYPE_OPAQUE )
        {
          return -1;
        }
        return -1;
    }


    /**
     * \brief    Set the value of the data value element as opaque.
     *
     *             Sets the value of the data element as as opaque.
     *
     *     \param    val        Value to set.
     *     \param    len        Length of the Value to set.
     *
     *     \return 0 on success.
     */
    int16_t setVal( uint8_t* val, uint16_t len ) {
        if( m_type == TYPE_STRING )
        {
            if( len > (DEVICEDATAVALUE_STRMAX-1) )
              return -1;
            memcpy( &m_val.cStr, val, len );
            m_val.cStr[len] = 0;
            return 0;
        }
        else if( m_type == TYPE_INTEGER )
        {
          switch( len )
          {
            case 1:
              m_val.i32 = (int8_t)val[0];
              return 1;
              break;

            case 2:
            {
              int16_t value;
              memcpy( &value, val, len );
              value = htons( value );

              m_val.i32 = value;
              return 1;
              break;
            }

            case 4:
            {
              int32_t value;
              memcpy( &value, val, len );
              value = htonl( value );

              m_val.i32 = value;
              return 1;
              break;
            }
          }
        }
        else if( m_type == TYPE_FLOAT )
        {

          return -1;
        }
        else if ( m_type == TYPE_OPAQUE )
        {
          if( len > DEVICEDATAVALUE_OPAQUEMAX )
            return -1;
          memcpy( &m_val.u_opaque.val, val, len );
        }
        return -1;
    }

private:

    /** type of the value */
    e_type m_type;

    /** union of the value */
    u_val m_val;
};

#endif /* #ifndef __DEVICEDATAVALUE_H__ */

