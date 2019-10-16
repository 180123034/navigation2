// Copyright (c) 2018 Intel Corporation
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef NAV2_BEHAVIOR_TREE__BACK_UP_ACTION_HPP_
#define NAV2_BEHAVIOR_TREE__BACK_UP_ACTION_HPP_

#include <string>
#include <memory>
#include <cmath>

#include "nav2_behavior_tree/bt_action_node.hpp"
#include "nav2_msgs/action/back_up.hpp"

namespace nav2_behavior_tree
{

class BackUpAction : public BtActionNode<nav2_msgs::action::BackUp>
{
public:
  explicit BackUpAction(
    const std::string & action_name,
    const BT::NodeParameters & params)
  : BtActionNode<nav2_msgs::action::BackUp>(action_name, params)
  {
  }

  void on_init() override
  {
    double dist;
    getParam<double>("backup_dist", dist);
    double speed;
    getParam<double>("backup_speed", speed);

    // silently fix, vector direction determined by distance sign
    if (speed < 0.0) {
      speed *= -1.0;
    }

    // Populate the input message
    goal_.target.x = dist;
    goal_.target.y = 0.0;
    goal_.target.z = 0.0;
    goal_.speed = speed;
  }

  static const BT::NodeParameters & requiredNodeParameters()
  {
    static BT::NodeParameters params = {
      {"backup_dist", "-0.15"}, {"backup_speed", "0.025"}};
    return params;
  }
};

}  // namespace nav2_behavior_tree

#endif  // NAV2_BEHAVIOR_TREE__BACK_UP_ACTION_HPP_