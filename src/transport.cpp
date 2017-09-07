/******************************************************************************
 *  Copyright (c) 2017, Intermodalics BVBA                                    *
 *  All rights reserved.                                                      *
 ******************************************************************************/

#include <rtt_pcl/typekit/Types.hpp>

#include <rtt/types/TransportPlugin.hpp>
#include <rtt/types/TypekitPlugin.hpp>

#include <rtt_roscomm/rtt_rostopic.h>
#include <rtt_roscomm/rtt_rostopic_ros_msg_transporter.hpp>

#include <pcl_ros/point_cloud.h>

namespace rtt_pcl_ros {

using namespace RTT::types;
using namespace pcl;

class ROSTransportPlugin : public TransportPlugin {
public:
  virtual bool registerTransport(std::string type_name, TypeInfo* ti) {
    #define _RTT_PCL_ADD_PROTOCOL(r, data, PointT) \
      if (type_name == "/pcl/PointCloud" BOOST_PP_STRINGIZE(PointT)) { \
        return ti->addProtocol(ORO_ROS_PROTOCOL_ID, new rtt_roscomm::RosMsgTransporter< PointCloud<PointT> >()); \
      }
    BOOST_PP_SEQ_FOR_EACH(_RTT_PCL_ADD_PROTOCOL, _, RTT_PCL_POINT_TYPES)
    #undef _RTT_PCL_ADD_PROTOCOL

    return false;
  }

  virtual std::string getTransportName() const {
    return "ros";
  }

  virtual std::string getTypekitName() const {
    return "pcl-types";
  }

  virtual std::string getName() const {
    return "pcl-ros-transport";
  }

};

} // namespace rtt_pcl_ros

ORO_TYPEKIT_PLUGIN( rtt_pcl_ros::ROSTransportPlugin )
