/*
 * (C) 2010, Ruben Smits, ruben.smits@mech.kuleuven.be
 * Department of Mechanical Engineering,
 * Katholieke Universiteit Leuven, Belgium.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the copyright holder nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <rtt/RTT.hpp>
#include <rtt/plugin/Plugin.hpp>
#include <rtt/plugin/ServicePlugin.hpp>
#include <rtt/internal/GlobalService.hpp>

#include <ros/package.h>

using namespace RTT;
using namespace std;

void loadROSPackService(){
  RTT::Service::shared_ptr ros = RTT::internal::GlobalService::Instance()->provides("ros");

  ros->addOperation("find", &ros::package::getPath).doc(
      "Returns the fully-qualified path to a package, or an empty string if the package is not found");
}

using namespace RTT;
extern "C" {
  bool loadRTTPlugin(RTT::TaskContext* c){
    if (c != 0) return false;
    loadROSPackService();
    return true;
  }
  std::string getRTTPluginName (){
    return "rospack";
  }
  std::string getRTTTargetName (){
    return OROCOS_TARGET_NAME;
  }
}
