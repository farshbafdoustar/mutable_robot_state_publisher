^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Changelog for package robot_state_publisher
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

2.0.0 (2018-07-30)
------------------
* Renaming to mutable_robot_state_publisher so can be run in parallel with original version.
* Adding synchronization topic for updating URDF.
* Updates mimic joint list on URDF swap
  This change fixes the issue preventing mimic joints Transforms (TF's)
  from be updated with the URDF swapping schema. Previously, the MimicMap
  was set at the start time of the robot_state_publisher and could never
  be updated, even when a new mimic joint was added via URDFConfiguration
  message. Now, the RobotStatePublisher has complete control over the
  MimicMap and the JointStatePublisher needs to request an update on every
  callbackJointStates() invocation. The MimicMap is read-mutex locked for
  the callbackJointStates() calls, and exlusive write-mutex locked when
  it needs to updated on a URDF Swap. If the read-mutex fails, the a
  ROS WARN is issued and the mimic joint transforms are not updated.
* Updated URDFConfig message to signify XML is valid
* Updated Solver deps for message gen
* Removed extra include and added udrf pkg dep
* Added CMake catkin message gen dependancy
* URDF Swapping mechanisms added to robot_state_pub
* Removed depricated code and unused fk solver
* Merge pull request `#26 <https://github.com/MisoRobotics/mutable_robot_state_publisher/issues/26>`_ from xqms/remove-debug
  get rid of argv[0] debug output on startup
* get rid of argv[0] debug output on startup
* Contributors: David Lu!!, Ian McMahon, Max Schwarz, Ryan Sinnet

1.10.4 (2014-11-30)
-------------------
* Merge pull request `#21 <https://github.com/ros/robot_state_publisher/issues/21>`_ from rcodddow/patch-1
* Fix for joint transforms not being published anymore after a clock reset (e.g. when playing a bagfile and looping)
* Contributors: Ioan A Sucan, Robert Codd-Downey, Timm Linder

1.10.3 (2014-07-24)
-------------------
* add version depend on orocos_kdl >= 1.3.0
  Conflicts:
  package.xml
* Update KDL SegmentMap interface to optionally use shared pointers
  The KDL Tree API optionally uses shared pointers on platforms where
  the STL containers don't support incomplete types.
* Contributors: Brian Jensen, William Woodall

1.10.0 (2014-03-03)
-------------------
* minor style fixes
* Add support for mimic tag.
* Contributors: Ioan Sucan, Konrad Banachowicz
