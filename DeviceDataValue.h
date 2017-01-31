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

/*
 * --- DEFINES -------------------------------------------------------------- *
 */

/** maximum length of the value as a string */
#define DEVICEDATAVALUE_STRMAX            50

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
        TYPE_STRING
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
        m_val.i32 = 0;
        m_val.f = 0;
        memset( m_val.cStr, 0, DEVICEDATAVALUE_STRMAX );
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
        return -1;
    }

private:

    /** type of the value */
    e_type m_type;

    /** union of the value */
    u_val m_val;
};

#endif /* #ifndef __DEVICEDATAVALUE_H__ */

