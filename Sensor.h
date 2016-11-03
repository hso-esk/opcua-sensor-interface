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
 * \file    Sensor.h
 * \author  Institute of reliable Embedded Systems
 *          and Communication Electronics
 * \date    $Date$
 * \version $Version$
 *
 * \brief   Description of the general Sensor Interface.
 *
 *          The general Sensor Interface shall be used as base class for all
 *          kind of specific sensors.
 */


#ifndef __SENSOR_H__
#define __SENSOR_H__
#ifndef __DECL_SENSOR_H__
#define __DECL_SENSOR_H__ extern
#endif /* #ifndef __DECL_SENSOR_H__ */


/*
 * --- Includes ------------------------------------------------------------- *
 */
#include <stdint.h>
#include <iostream>
#include <string>

/*
 * --- Class Definition ----------------------------------------------------- *
 */

/**
 * \brief   General Sensor Class.
 *
 *          The Sensor Class provides the base class for all sensors.
 */
class Sensor
{

public:

    /**
     * \brief   Default Constructor to create a sensor.  
     */
    Sensor();

    /**
     * \brief   Constructor to create a sensor with a specific name.
     *
     *          This constructor can be used to create a sensor with
     *          a specific name.
     */
    Sensor( std::string name );

    /**
     * \brief   Default Destructor of the sensor.
     */
	virtual ~Sensor();

    /**
     * \brief   Get the name of the sensor.
     *
     * \return  The name of the sensor.
     */
    std::string getName( void );

    /**
     * \brief   Set the name of the sensor.
     *
     * \param   name    Name to give to the sensor.
     */
    void setName( std::string name );

private:

    /** name of the sensor */
    std::string m_name;
	
};

#endif /* #ifndef __SENSOR_H__ */

