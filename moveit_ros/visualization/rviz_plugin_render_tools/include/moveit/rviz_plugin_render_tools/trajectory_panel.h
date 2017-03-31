#ifndef MOVEIT_TRAJECTORY_RVIZ_PLUGIN__TRAJECTORY_PANEL
#define MOVEIT_TRAJECTORY_RVIZ_PLUGIN__TRAJECTORY_PANEL

#include <rviz/panel.h>
#include <rviz/properties/bool_property.h>
#include <ros/ros.h>
#include <QSlider>
#include <QLabel>
#include <moveit/rviz_plugin_render_tools/robot_state_visualization.h>
#include <moveit/robot_trajectory/robot_trajectory.h>
#include <QPushButton>

namespace moveit_rviz_plugin
{

class TrajectoryPanel : public rviz::Panel
{
  Q_OBJECT

public:
  TrajectoryPanel (QWidget* parent = 0);

  virtual ~TrajectoryPanel();

  void onInitialize(RobotStateVisualizationPtr& display_path_robot, rviz::BoolProperty* loop_display_property);
  void onEnable();
  void onDisable();
  void update(robot_trajectory::RobotTrajectoryPtr& displaying_trajectory_message);
  void setSliderPosition(int position);
  int getSliderPosition();
  void checkButton(bool check);

private Q_SLOTS:
  void showWaypoint(int waypoint);
  void loopStopEnable(bool enable); 

protected:
  QSlider* slider_;
  QLabel* maximum_label_;
  QPushButton* button_;

  RobotStateVisualizationPtr display_path_robot_;
  rviz::BoolProperty* loop_display_property_;

//  bool* paused_loop_;
  robot_trajectory::RobotTrajectoryPtr displaying_trajectory_message_;
};

} // end namespace moveit_rviz_plugin

#endif // TRAJECTORY_PANEL
