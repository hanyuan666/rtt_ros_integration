/***************************************************************************
  tag: Ruben Smits  Tue Nov 16 09:19:02 CET 2010  ros_plugin.cpp

                        ros_plugin.cpp -  description
                           -------------------
    begin                : Tue November 16 2010
    copyright            : (C) 2010 Ruben Smits
    email                : first.last@mech.kuleuven.be

 ***************************************************************************
 *   This library is free software; you can redistribute it and/or         *
 *   modify it under the terms of the GNU Lesser General Public            *
 *   License as published by the Free Software Foundation; either          *
 *   version 2.1 of the License, or (at your option) any later version.    *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 59 Temple Place,                                    *
 *   Suite 330, Boston, MA  02111-1307  USA                                *
 *                                                                         *
 ***************************************************************************/


#include <rtt/plugin/Plugin.hpp>
#include <rtt/TaskContext.hpp>
#include <rtt/Activity.hpp>
#include <rtt/Logger.hpp>
#include <rtt/os/startstop.h>
#include <ros/ros.h>

void loadROSService();
void loadROSPackService();

using namespace RTT;
extern "C" {
  bool loadRTTPlugin(RTT::TaskContext* c){
    log(Info)<<"Initializing ROS node"<<endlog();
    if(!ros::isInitialized()){
        int argc =__os_main_argc();
        char ** argv = __os_main_argv();
        ros::init(argc,argv,"rtt",ros::init_options::AnonymousName);
      if(ros::master::check())
          ros::start();
      else{
          log(Error)<<"No ros::master available"<<endlog();
          ros::shutdown();
          return false;
      }
    }
    static ros::AsyncSpinner spinner(1); // Use 1 threads
    spinner.start();
    log(Info)<<"ROS node spinner started"<<endlog();

    loadROSService();
    loadROSPackService();
    return true;
  }
  std::string getRTTPluginName (){
    return "ros_integration";
  }
  std::string getRTTTargetName (){
    return OROCOS_TARGET_NAME;
  }
}
