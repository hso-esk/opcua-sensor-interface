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
 * \file    DeviceData.h
 * \author  Institute of reliable Embedded Systems
 *          and Communication Electronics
 * \date    $Date$
 * \version $Version$
 *
 * \brief   Description of a single device data element.
 *
 *          A device consist of several device elements. A device data element
 *          for example can be a variable or value that can be read or written.
 */


#ifndef __DEVICEDATA_H__
#define __DEVICEDATA_H__
#ifndef __DECL_DEVICEDATA_H__
#define __DECL_DEVICEDATA_H__ extern
#endif /* #ifndef __DECL_DEVICEDATA_H__ */


/*
 * --- Includes ------------------------------------------------------------- *
 */
#include <stdint.h>
#include <iostream>
#include <string>
#include <vector>
#include "DeviceDataValue.h"


/*
 * --- Forward Declaration ----------------------------------------------------- *
 */
class DeviceDataObserver;

/*
 * --- Class Definition ----------------------------------------------------- *
 */

/**
 * \brief   DeviceData Class.
 *
 *          A device data represents a single value of a device
 *          that can be read or written. Since the device data can be
 *          of different types this class is implemented as a template.
 */
class DeviceData
{

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
     * \brief   Default Constructor to create a Device element.
     */
    DeviceData( void )
        : m_name( "undefined" )
        , m_descr( "undefined" )
        , m_readable( true )
        , m_writable( false )
        , m_observable( false )
        , m_observed( false )
        , m_val( DeviceDataValue(DeviceDataValue::TYPE_INTEGER) )
        {};

    /**
     * \brief   Constructor with a specific default name and description.
     *
     * \param   name    Name of the device data element.
     * \param   desc    Description of the device data element.
     * \param    type    Type of the data value.
     * \param    access    Access permissions.
     */
    DeviceData( std::string name, std::string descr, DeviceDataValue::e_type type,
            int access )
        : m_name( name )
        , m_descr( descr )
        , m_readable( access & DeviceData::ACCESS_READ )
        , m_writable( access & DeviceData::ACCESS_WRITE )
        , m_observable( access & DeviceData::ACCESS_OBSERVE )
        , m_observed( false )
        , m_val( type ) {

        /* reset vector */
        m_obs.clear();
    };

    /**
     * \brief   Default Destructor of the device element.
     */
    virtual ~DeviceData( void ) {};

    /**
     * \brief   Get the name of the device data element.
     *
     * \return  The name of the device data element.
     */
    std::string getName( void ) {
        /* return name */
        return m_name;
    }

    /**
     * \brief   Get the description of the device data element.
     *
     * \return  The description of the device data element.
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
     * \brief   Get the actual value device data element.
     *
     * \return  The actual value of the device data element.
     */
    const DeviceDataValue* getVal( void );

    /**
     * \brief   Set the actual value device data element.
     *
     * \param   val     Value to set the device data to.
     *
     * \return  returns true if the value was set.
     */
    int16_t setVal( const DeviceDataValue* val );

    /**
     * \brief   Observe the actual value device data element.
     *
     *          If a value is observed a specific callback function
     *          will be called whenever the value changes.
     *
     * \param   pf_obs       Observer.
     * \param   p_param      Additional parameter that will given as
     *                       parameter to the callback function.
     *
     * \return  returns true if the value is observed.
     */
    int16_t observeVal( DeviceDataObserver* p_obs, void* p_param );

protected:

    /**
     * \brief    Indicates that a value changed.
     *
     *             This function shall be called from the sub
     *             classes whenever an according value changed.
     *
     * \param    val        The new value.
     */
    void valueChanged( const DeviceDataValue* val );

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
    virtual int16_t getValNative( DeviceDataValue* val ) = 0;

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
    virtual int16_t setValNative( const DeviceDataValue* val ) = 0;

    /**
     * \brief   Native function to observe the device data value.
     *
     *          A device can be accessed using different types of mechanisms
     *          or protocols (e.g. ProfiBus, LWM2M). Therefore, the observe
     *           function is the interface from the abstract device data
     *          description and the actual protocol dependent implementation.
     *          Each device type has to implement this function accordingly.
     *
     * \return  0 on success.
     */
    virtual int8_t observeValNative( void ) = 0;

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
    DeviceDataValue m_val;

    struct s_obs{
        /** observer */
        DeviceDataObserver* p_obs;
        /** parameter */
        void* p_param;
    };

    /** vector including all the registered observer */
    std::vector< s_obs > m_obs;
};

#endif /* #ifndef __DEVICEDATA_H__ */

