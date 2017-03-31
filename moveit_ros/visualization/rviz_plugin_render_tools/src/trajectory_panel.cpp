#include <moveit/rviz_plugin_render_tools/trajectory_panel.h>
#include <QHBoxLayout>
#include <QLabel>

namespace moveit_rviz_plugin
{

TrajectoryPanel::TrajectoryPanel (QWidget* parent)
  : Panel( parent )
{
}

TrajectoryPanel::~TrajectoryPanel()
{
}

void TrajectoryPanel::onInitialize(RobotStateVisualizationPtr& display_path_robot, rviz::BoolProperty* loop_display_property)
{
  display_path_robot_ = display_path_robot;
  //paused_loop_ = &paused_loop;
  loop_display_property_ = loop_display_property;

  slider_ = new QSlider(Qt::Horizontal);
  slider_->setTickInterval(1);
  slider_->setMinimum(0);
  slider_->setMaximum(0);
  connect(slider_, SIGNAL(valueChanged(int)), this, SLOT(showWaypoint(int))); 

  QHBoxLayout* layout = new QHBoxLayout;
  maximum_label_ = new QLabel(QString::number(slider_->maximum()));
  button_ = new QPushButton();
  button_->setText("Pause");
  button_->setCheckable(true);
  connect(button_, SIGNAL(toggled(bool)), this, SLOT(loopStopEnable(bool)));

  layout->addWidget(new QLabel("Waypoint:"));
  layout->addWidget(new QLabel("0"));
  layout->addWidget(slider_);
  layout->addWidget(maximum_label_);
  layout->addWidget(button_);
  setLayout(layout);
}

void TrajectoryPanel::onEnable()
{
  parentWidget()->show();
}

void TrajectoryPanel::onDisable()
{
  parentWidget()->hide();
}

void TrajectoryPanel::showWaypoint(int waypoint)
{
    display_path_robot_->setVisible(true);
    display_path_robot_->update(displaying_trajectory_message_->getWayPointPtr(waypoint));
}

void TrajectoryPanel::update(robot_trajectory::RobotTrajectoryPtr& displaying_trajectory_message)
{
  displaying_trajectory_message_ = displaying_trajectory_message;
  slider_->setSliderPosition(0);
  slider_->setMaximum(displaying_trajectory_message_->getWayPointCount()-1);
  maximum_label_->setText(QString::number(displaying_trajectory_message_->getWayPointCount()-1));
}

void TrajectoryPanel::setSliderPosition(int position)
{
  slider_->setSliderPosition(position);
}

void TrajectoryPanel::loopStopEnable(bool enable)
{
    loop_display_property_->setValue(enable);
  //*paused_loop_ = enable;
}

int TrajectoryPanel::getSliderPosition()
{
  return slider_->sliderPosition();
}

void TrajectoryPanel::checkButton(bool check)
{
  //button_->setChecked(check);
  if (check)
    button_->setText("play");
  else 
    button_->setText("pause");
  //loopStopEnable(check);
}

} // end namespace moveit_rviz_plugin
