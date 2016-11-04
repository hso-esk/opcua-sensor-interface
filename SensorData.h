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


#ifndef __SENSORDATA_H__
#define __SENSORDATA_H__
#ifndef __DECL_SENSORDATA_H__
#define __DECL_SENSORDATA_H__ extern
#endif /* #ifndef __DECL_SENSORDATA_H__ */


/*
 * --- Includes ------------------------------------------------------------- *
 */
#include <stdint.h>
#include <iostream>
#include <string>
#include <vector>
#include "SensorDataValue.h"

/*
 * --- Class Definition ----------------------------------------------------- *
 */

/**
 * \brief   SensorData Class.
 *
 *          A sensor data represents a single value of a sensor
 *          that can be read or written. Since the sensor data can be
 *          of different types this class is implemented as a template.
 */
class SensorData
{

	/**
	 * \brief	Callback function definition for observing data.
	 *
	 * 			Data cannot only be written and read but also
	 * 			observed. To observe sensor data a callback
	 * 			function has to be given which shall be called
	 * 			whenever the observed value changes.
	 *
	 * \param   p_val   	Name of the sensor data value that changed.
	 * \param   p_param    	User parameter.
	 */
	typedef void (*pf_observeCB)( const SensorDataValue* p_val, void* p_param );

public:

	/** Enumeration for the different types of access */
	enum e_access
	{
		/** no Access */
		ACCESS_NONE = 0x00,
		/** read access */
		ACCESS_READ = 0x01,
		/** write access */
		ACCESS_WRITE = 0x02,
		/** observe access */
		ACCESS_OBSERVE = 0x04
	};


    /**
     * \brief   Default Constructor to create a Sensor element.
     */
    SensorData( void )
		: m_name( "undefined" )
		, m_descr( "undefined" )
		, m_readable( true )
		, m_writable( false )
		, m_observable( false )
		, m_observed( false )
		, m_val( SensorDataValue(SensorDataValue::TYPE_INTEGER) )
		{};

    /**
     * \brief   Constructor with a specific default name and description.
     *
     * \param   name    Name of the sensor data element.
     * \param   desc    Description of the sensor data element.
     */
    SensorData( std::string name, std::string descr, SensorDataValue::e_type type,
    		int access )
		: m_name( name )
		, m_descr( descr )
		, m_readable( access & SensorData::ACCESS_READ )
		, m_writable( access & SensorData::ACCESS_WRITE )
		, m_observable( access & SensorData::ACCESS_OBSERVE )
		, m_observed( false )
		, m_val( type ) {

    	/* reset vector */
    	m_cbs.clear();
    };

    /**
     * \brief   Default Destructor of the sensor element.
     */
	virtual ~SensorData( void ) {};

    /**
     * \brief   Get the name of the sensor data element.
     *
     * \return  The name of the sensor data element.
     */
    std::string getName( void ) {
    	/* return name */
    	return m_name;
    }

    /**
     * \brief   Get the description of the sensor data element.
     *
     * \return  The description of the sensor data element.
     */
    std::string getDescr( void ) {
    	/* return description */
    	return m_descr;
    }

    /**
     * \brief   Check if the value is writable.
     *
     * \return  true or false depending on if the value is writable.
     */
    bool getWritable( void ) {
    	/* return writable attribute */
    	return m_writable;
    }

    /**
     * \brief   Check if the value is readable.
     *
     * \return  true or false depending on if the value is readable.
     */
    bool getReadable( void ) {
    	/* return readable attribute */
    	return m_readable;
    }

    /**
     * \brief   Check if the value is readable.
     *
     * \return  true or false depending on if the value is readable.
     */
    bool getObserveable( void ) {
    	/* return readable attribute */
    	return m_observable;
    }

    /**
     * \brief   Get the actual value sensor data element.
     *
     * \return  The actual value of the sensor data element.
     */
    const SensorDataValue* getVal( void );

    /**
     * \brief   Set the actual value sensor data element.
     *
     * \param   val     Value to set the sensor data to.
     *
     * \return  returns true if the value was set.
     */
    int16_t setVal( const SensorDataValue* val );

    /**
     * \brief   Observe the actual value sensor data element.
     *
     * 			If a value is observed a specific callback function
     * 			will be called whenever the value changes.
     *
     * \param	pf_cb		Callback function.
     * \param   p_param		Additional parameter that will given as
     * 						parameter to the callback function.
     *
     * \return  returns true if the value is observed.
     */
    int16_t observeVal( pf_observeCB pf_cb, void* p_param );

protected:

    /**
     * \brief	Indicates that a value changed.
     *
     * 			This function shall be called from the sub
     * 			classes whenever an according value changed.
     *
     * \param	val		The new value.
     */
    void valueChanged( const SensorDataValue* val );

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
    virtual int16_t getValNative( SensorDataValue* val ) = 0;
    
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
    virtual int16_t setValNative( const SensorDataValue* val ) = 0;

private:

    /** name of the data element */
    std::string m_name;

    /** description of the data element */
    std::string m_descr;

    /** defines if the value is readable */
    bool m_readable;

    /** defines if the value is writable */
    bool m_writable;

    /** defines if the value is observable */
    bool m_observable;

    /** value is observed */
    bool m_observed;

    /** The actual value */
    SensorDataValue m_val;

    struct s_cb{
    	/** callback function */
    	pf_observeCB pf_cb;
    	/** parameter */
    	void* p_param;
    };

    /** vector including all the registered callbacks */
    std::vector< s_cb > m_cbs;
};

#endif /* #ifndef __SENSORDATA_H__ */

