/*
 * Copyright (C) 2007-2013 Istituto Italiano di Tecnologia ADVR & iCub Facility
 * Authors: Enrico Mingo, Alessio Rocchi, Mirko Ferrati, Silvio Traversaro and Alessandro Settimi
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 */


#include <gazebo_yarp_plugins/ForceTorque.hh>
#include <gazebo_yarp_plugins/ForceTorqueDriver.h>

#include <yarp/dev/PolyDriver.h>
#include <yarp/dev/Wrapper.h>

#include <gazebo/sensors/ForceTorqueSensor.hh>
#include "gazebo_yarp_plugins/Handler.hh"


using namespace gazebo;

GZ_REGISTER_SENSOR_PLUGIN(GazeboYarpForceTorque)

#define toDeg(X) (X*180.0/M_PI)

GazeboYarpForceTorque::GazeboYarpForceTorque() : SensorPlugin(), _yarp()
{
}

void GazeboYarpForceTorque::Init()
{
    std::cout<<"*** GazeboYarpForceTorque plugin started ***"<<std::endl;
    if (!_yarp.checkNetwork())
        std::cout<<"Sorry YARP network does not seem to be available, is the yarp server available?"<<std::endl;
    else
        std::cout<<"YARP Server found!"<<std::endl;
}

GazeboYarpForceTorque::~GazeboYarpForceTorque()
{
    std::cout<<"*** GazeboYarpForceTorque closing ***"<<std::endl;
    _forcetorque_driver.close();
    GazeboYarpPluginHandler::getHandler()->removeSensor(_sensorName);
}

void GazeboYarpForceTorque::Load(sensors::SensorPtr _sensor, sdf::ElementPtr _sdf)
{
    
    if (!_sensor)
    {
        gzerr << "GazeboYarpForceTorque plugin requires a ForceTorqueSensor.\n";
        return;
    }

    _sensor->SetActive(true);

    // Add my gazebo device driver to the factory.
    yarp::dev::Drivers::factory().add(new yarp::dev::DriverCreatorOf<yarp::dev::GazeboYarpForceTorqueDriver>
                                      ("gazebo_forcetorque", "analogServer", "GazeboYarpForceTorqueDriver"));
        
    //Getting .ini configuration file from sdf
    
    yarp::os::Property wrapper_properties;
    yarp::os::Property driver_properties;
    bool configuration_loaded = false;
        
    if(_sdf->HasElement("yarpConfigurationFile") )
    {
        std::string ini_file_name = _sdf->Get<std::string>("yarpConfigurationFile");
        std::string ini_file_path = gazebo::common::SystemPaths::Instance()->FindFileURI(ini_file_name);

        if( ini_file_path != "" && driver_properties.fromConfigFile(ini_file_path.c_str()) )
        {
            std::cout << "Found yarpConfigurationFile: loading from " << ini_file_path << std::endl;
            configuration_loaded = true;
        }
    }
    
    ///< \todo TODO handle in a better way the parameters that are for the wrapper and the one that are for driver
    wrapper_properties = driver_properties;
        
    if( !configuration_loaded )
    {
        std::cout << "File .ini not found, quitting\n" << std::endl;
        return;
    }
    
    _sensorName = _sensor->GetScopedName();
    //Insert the pointer in the singleton handler for retriving it in the yarp driver
    GazeboYarpPluginHandler::getHandler()->setSensor(boost::get_pointer(_sensor));
    
    driver_properties.put(yarp_scopedname_parameter.c_str(), _sensorName.c_str());
    
    //Open the wrapper
    //Force the wrapper to be of type "analogServer" (it make sense? probably no)
    wrapper_properties.put("device","analogServer");
    if( _forcetorque_wrapper.open(wrapper_properties) ) {
        std::cout<<"GazeboYarpForceTorque Plugin: correcly opened GazeboYarpForceTorqueDriver wrapper"<<std::endl;
    } else {
        std::cout<<"GazeboYarpForceTorque Plugin failed: error in opening yarp driver wrapper"<<std::endl;
        return;
    }
   
    //Open the driver
    //Force the device to be of type "gazebo_forcetorque" (it make sense? probably yes)
    driver_properties.put("device","gazebo_forcetorque");
    if( _forcetorque_driver.open(driver_properties) ) {
        std::cout<<"GazeboYarpForceTorque Plugin: correcly opened GazeboYarpForceTorqueDriver"<<std::endl;
    } else {
        std::cout<<"GazeboYarpForceTorque Plugin failed: error in opening yarp driver"<<std::endl;
        return;
    }
    
    //Attach the driver to the wrapper
    yarp::dev::IMultipleWrapper * iWrap;
    yarp::dev::PolyDriverList driver_list;
    
    if( !_forcetorque_wrapper.view(iWrap) ) {
        std::cerr << "GazeboYarpForceTorque : error in loading wrapper" << std::endl;
        return;
    }
    
    driver_list.push(&_forcetorque_driver,"dummy");
    
    if( iWrap->attachAll(driver_list) ) {
        std::cerr << "GazeboYarpForceTorque : wrapper was connected with driver " << std::endl;
    } else {
        std::cerr << "GazeboYarpForceTorque : error in connecting wrapper and device " << std::endl;
    }
    
}
