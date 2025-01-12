/*********************************************************************
 * Software License Agreement (BSD License)
 *
 *  Copyright (c) 2008, Willow Garage, Inc.
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   * Neither the name of the Willow Garage nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 *********************************************************************/

/* Author: Wim Meeussen */

#ifndef ROBOT_STATE_PUBLISHER_H
#define ROBOT_STATE_PUBLISHER_H

#include <boost/scoped_ptr.hpp>
#include <boost/thread/shared_mutex.hpp>

#include <kdl/frames.hpp>
#include <kdl/segment.hpp>
#include <kdl/tree.hpp>
#include <mutable_robot_state_publisher/robot_kdl_tree.h>
#include <ros/ros.h>
#include <tf/tf.h>
#include <tf/transform_broadcaster.h>
#include <urdf/model.h>

typedef std::map<std::string, boost::shared_ptr<urdf::JointMimic> > MimicMap;
namespace mutable_robot_state_publisher
{

class SegmentPair
{
public:
  SegmentPair(const KDL::Segment& p_segment, const std::string& p_root, const std::string& p_tip)
    : segment(p_segment), root(p_root), tip(p_tip)
  {
  }

  KDL::Segment segment;
  std::string root, tip;
};

class RobotStatePublisher : public robot_kdl_tree::RobotKDLTree
{
  ros::NodeHandle nh_;

public:
  virtual bool init();

  virtual void onURDFSwap(const std::string& link_name);

  /** Constructor
   * \param tree The kinematic model of a robot, represented by a KDL Tree
   */
  RobotStatePublisher(const urdf::Model m);

  /// Destructor
  ~RobotStatePublisher(){};

  /** Publish transforms to tf
   * \param joint_positions A map of joint names and joint positions.
   * \param time The time at which the joint positions were recorded
   */
  void publishTransforms(const std::map<std::string, double>& joint_positions, const ros::Time& time,
                         const std::string& tf_prefix);
  void publishFixedTransforms();
  void publishFixedTransforms(const std::string& tf_prefix);
  void setRobotDescriptionIfChanged();
  void setJointMimicMap(const urdf::Model& model);
  bool getJointMimicPositions(std::map<std::string, double>& joint_positions);

private:
  void addChildren(const KDL::SegmentMap::const_iterator segment);

  std::map<std::string, SegmentPair> segments_, segments_fixed_;
  tf::TransformBroadcaster tf_broadcaster_;

  bool initialized_;
  bool urdf_changed_;
  MimicMap mimic_;
  boost::shared_mutex mimic_mtx_;
  ros::Publisher urdf_update_pub_;
};

}  // namespace mutable_robot_state_publisher

#endif
