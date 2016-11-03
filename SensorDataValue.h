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
 * \file    SensorData.h
 * \author  Institute of reliable Embedded Systems
 *          and Communication Electronics
 * \date    $Date$
 * \version $Version$
 *
 * \brief   Description of a single sensor data element.
 *
 *          A sensor consist of several sensor elements. A sensor data element
 *          for example can be a variable or value that can be read or written.
 */


#ifndef __SENSORDATAVALUE_H__
#define __SENSORDATAVALUE_H__
#ifndef __DECL_SENSORDATAVALUE_H__
#define __DECL_SENSORDATAVALUE_H__ extern
#endif /* #ifndef __DECL_SENSORDATAVALUE_H__ */


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
#define SENSORDATAVALUE_STRMAX			50

/*
 * --- Class Definition ----------------------------------------------------- *
 */
class SensorDataValue
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
		char cStr[SENSORDATAVALUE_STRMAX];
	};

	/** overloaded comparison operator */
	friend bool operator== (const SensorDataValue& cmp1,
			const SensorDataValue& cmp2) {

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
	friend bool operator!= (const SensorDataValue& cmp1,
			const SensorDataValue& cmp2) {
		return ! (cmp1 == cmp2);
	}

    /**
     * \brief   Constructor with a specific default type.
     *
     * \param   type    Type of the value.
     */
	SensorDataValue( SensorDataValue::e_type type )
		: m_type( type ) {

		/* reset members */
		m_val.i32 = 0;
		m_val.f = 0;
		memset( m_val.cStr, 0, SENSORDATAVALUE_STRMAX );
	};

    /**
     * \brief   Default destructor.
     */
	virtual ~SensorDataValue( void ) {};

	/**
	 * \brief	Get the type of the value,
	 *
	 * 	\return Type of the value
	 */
	int16_t getType( void ) const {return m_type;}

	/**
	 * \brief	Get the actual value,
	 *
	 * 	\return The actual value
	 */
	u_val getVal( void ) const {return m_val;}

	/**
	 * \brief	Set the value of the data value element as integer,
	 *
	 * 			Sets the value of the data element as as integer. If
	 * 			the types do not match the value will not be assigned.
	 *
	 * 	\param	val		Value to set.
	 *
	 * 	\return 0 on success.
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
	 * \brief	Set the value of the data value element as float,
	 *
	 * 			Sets the value of the data element as as float. If
	 * 			the types do not match the value will not be assigned.
	 *
	 * 	\param	val		Value to set.
	 *
	 * 	\return 0 on success.
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
	 * \brief	Set the value of the data value element as string,
	 *
	 * 			Sets the value of the data element as as integer. If
	 * 			the types do not match the value will not be assigned.
	 *
	 * 	\param	val		Value to set.
	 *
	 * 	\return 0 on success.
	 */
	int16_t setVal( std::string val ) {
		if( m_type == TYPE_STRING )
		{
			size_t l = snprintf(m_val.cStr, SENSORDATAVALUE_STRMAX,
					"%s", val.c_str());

			/* remove trailing newline if it exists */
			if( (l > 1) && (m_val.cStr[l-1] == '\n') )
				m_val.cStr[l-1] = '\0';
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

#endif /* #ifndef __SENSORDATAVALUE_H__ */

