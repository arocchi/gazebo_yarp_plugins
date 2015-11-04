gazebo_yarp_plugins
===================

[![Join the chat at https://gitter.im/arocchi/gazebo_yarp_plugins](https://badges.gitter.im/Join%20Chat.svg)](https://gitter.im/arocchi/gazebo_yarp_plugins?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)
[![Build Status](https://travis-ci.org/robotology/gazebo_yarp_plugins.png)](https://travis-ci.org/robotology/gazebo_yarp_plugins)

Plugins for exposing [Yarp](http://yarp.it/) interfaces on [Gazebo simulator](http://gazebosim.org/) models. 

Installation
------------
### Dependencies 
For using Yarp with Gazebo, you shall install:
 * Gazebo simulator (at least version 2.0), following the [instructions on the official Gazebo website](http://gazebosim.org/wiki/Install).
 * Yarp (in the version available in the master branch of the yarp repository) following the [instructions on the official Yarp wiki](http://wiki.icub.org/wiki/Linux:Installation_from_sources#Getting_the_YARP_and_iCub_sources) and enabling the CREATE_SHARED_LIBRARY CMake option to compile Yarp as a shared library.


###Compile time dependencies
For compiling gazebo_yarp_plugins you need the headers for the following libraries:
  * [tinyxml](http://www.grinninglizard.com/tinyxml/)
  * [Boost System](www.boost.org/doc/libs/release/libs/system/)

For example on Ubuntu you can install them with the following command:
```
sudo apt-get install libtinyxml-dev libboost-system-dev
```
On OS X you can instead use brew:
```
brew install tinyxml boost
```



### Operating systems support 
Linux and OS X are currently supported by Gazebo. 
OS X support in Gazebo is still experimental, and there could be problems.

### Compilation 
You get the gazebo_yarp_plugins source code from this git repository repository (if you do not have git on your computer, [follow this guide to install it](http://git-scm.com/downloads))
```
git clone https://github.com/robotology/gazebo_yarp_plugins.git
```
This will create a gazebo_yarp_plugins directory with all the source code.
You can enter this directory:
```
cd gazebo_yarp_plugins
```
You can then create a build directory inside it to hold all the compiled files:
```
mkdir build
```
You can use CMake to generate the necessary file for the compilation, and compile gazebo_yarp_plugins using make:
```
cd build
cmake ../
make
```

To notify Gazebo of the new plugins compiled, it is necessary to modify the GAZEBO_PLUGIN_PATH enviroment variable: 
```
export GAZEBO_PLUGIN_PATH=${GAZEBO_PLUGIN_PATH}:/path/to/gazebo_yarp_plugins/build
```
Where "/path/to/gazebo_yarp_plugins/build" is the path on your computer where you located the build directory.
To avoid having to modify this enviroment variable each time, you can place this command in the .bashrc file in your home directory.

You can decide to install the plugins by issuing a
```
sudo make install
```
at which point you need to update the GAZEBO_PLUGIN_PATH accordingly, if the installation path is not in the LD_LIBRARY_PATH of your system

Usage
-----
To use the gazebo_yarp_plugins you can try to use a Yarp-enabled Gazebo model of a robot. Currently two robot support gazebo_yarp_plugins: Coman and iCub.

### Coman
To use Coman in Gazebo, please follow [the instructions on gazebo_yarp_plugins wiki](https://github.com/robotology/gazebo_yarp_plugins/wiki/Using-Coman-model-with-gazebo_yarp_plugins)

### iCub 
To use iCub in Gazebo, please follow [the instruction in the icub_gazebo repository](https://github.com/robotology-playground/icub_gazebo)

### Arbitrary robot
To add gazebo_yarp_plugins to another robot, please follow the instructions on [gazebo_yarp_plugins wiki](https://github.com/robotology/gazebo_yarp_plugins/wiki/Embed-gazebo_yarp_plugins-in-a-SDF-model)

Troubleshooting
---------------
- If gazebo_yarp_plugins does not compile complaning about an -fPIC option missing, check that you compiled yarp with shared library option enabled.

- If Gazebo complains about not finding the libgazebo_yarp_*.so files, check if you properly defined the GAZEBO_PLUGIN_PATH enviroment variable.

- If Gazebo complains that a yarp server is not available, remember to launch a yarp server on your machine (i.e. open a new terminal a launch the yarpserver command).

- If the simulation run slowly, check that you are using the latest graphics driver available for your platform. If you a running a recent Ubuntu version (13.10 or 14.04) you can try (at your own risk) to use the drivers provided by the [oibaf PPA](https://launchpad.net/~oibaf/+archive/graphics-drivers).


Design
------
More information on the internal structure of gazebo_yarp_plugins is [available in this wiki page](https://github.com/robotology/gazebo_yarp_plugins/wiki/Design).


Contributing
------------
If you would like to contribute to the development of gazebo_yarp_plugins, please get in contact with the development team using [GitHub issues](https://github.com/robotology/gazebo_yarp_plugins/issues). 



