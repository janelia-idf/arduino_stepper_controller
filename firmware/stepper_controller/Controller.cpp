// ----------------------------------------------------------------------------
// Controller.cpp
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#include "Controller.h"

Controller::Controller()
{
  waypoint_repeating_ = false;
}

void Controller::setup()
{
  EventController::event_controller.setup();
  Timer1.initialize();
  motor_drive_.setup();
  Timer1.attachInterrupt(callbacks::motorDriveCallback);
  attachMotionInterrupts();
  attachSoundInterrupts();

  // Pin Setup

  // Device Info
  globals::modular_server.setName(constants::device_name);
  globals::modular_server.setModelNumber(constants::model_number);
  globals::modular_server.setFirmwareVersion(constants::firmware_major,constants::firmware_minor,constants::firmware_patch);

  // Add Server Streams
  globals::modular_server.addServerStream(Serial);

  // Set Storage
  globals::modular_server.setFieldStorage(fields_);
  globals::modular_server.setParameterStorage(parameters_);
  globals::modular_server.setMethodStorage(methods_);

  // Fields
  // ModularDevice::Field& mode_field = globals::modular_server.createField(constants::mode_field_name,constants::mode_default);

  ModularDevice::Field& micro_steps_per_step_field = globals::modular_server.createField(constants::micro_steps_per_step_field_name,constants::micro_steps_per_step_default);
  micro_steps_per_step_field.setRange(constants::micro_steps_per_step_min,constants::micro_steps_per_step_max);

  ModularDevice::Field& waypoint_count_field = globals::modular_server.createField(constants::waypoint_count_field_name,constants::waypoint_count_default);
  waypoint_count_field.setRange(constants::waypoint_count_min,constants::waypoint_count_max);
  waypoint_count_field.attachSetValueCallback(callbacks::setWaypointCountCallback);

  ModularDevice::Field& waypoint_travel_duration_field = globals::modular_server.createField(constants::waypoint_travel_duration_field_name,constants::waypoint_travel_duration_default);
  waypoint_travel_duration_field.setRange(constants::waypoint_travel_duration_min,constants::waypoint_travel_duration_max);
  waypoint_travel_duration_field.setUnits(constants::duration_parameter_units);
  waypoint_travel_duration_field.attachSetValueCallback(callbacks::setWaypointTravelDurationCallback);

  ModularDevice::Field& reverse_direction_field = globals::modular_server.createField(constants::reverse_direction_field_name,constants::reverse_direction_default);

  ModularDevice::Field& enable_polarity_high_field = globals::modular_server.createField(constants::enable_polarity_high_field_name,constants::enable_polarity_high_default);

  ModularDevice::Field& tone_frequency_field = globals::modular_server.createField(constants::tone_frequency_field_name,constants::tone_frequency_default);
  tone_frequency_field.setRange(constants::tone_frequency_min,constants::tone_frequency_max);
  tone_frequency_field.setUnits(constants::frequency_parameter_units);

  ModularDevice::Field& tone_duration_field = globals::modular_server.createField(constants::tone_duration_field_name,constants::tone_duration_default);
  tone_duration_field.setRange(constants::tone_duration_min,constants::tone_duration_max);
  tone_duration_field.setUnits(constants::duration_parameter_units);

  ModularDevice::Field& play_tone_before_move_field = globals::modular_server.createField(constants::play_tone_before_move_field_name,constants::play_tone_before_move_default);

  ModularDevice::Field& waypoint_repeat_field = globals::modular_server.createField(constants::waypoint_repeat_field_name,constants::waypoint_repeat_default);

  ModularDevice::Field& waypoint_repeat_period_field = globals::modular_server.createField(constants::waypoint_repeat_period_field_name,constants::waypoint_repeat_period_default);
  waypoint_repeat_period_field.setRange(constants::waypoint_repeat_period_min,constants::waypoint_repeat_period_max);
  waypoint_repeat_period_field.setUnits(constants::duration_parameter_units);

  // Parameters

  // Methods
  ModularDevice::Method& enable_method = globals::modular_server.createMethod(constants::enable_method_name);
  enable_method.attachCallback(callbacks::enableCallback);

  ModularDevice::Method& disable_method = globals::modular_server.createMethod(constants::disable_method_name);
  disable_method.attachCallback(callbacks::disableCallback);

  ModularDevice::Method& stop_method = globals::modular_server.createMethod(constants::stop_method_name);
  stop_method.attachCallback(callbacks::stopCallback);

  ModularDevice::Method& get_controller_info_method = globals::modular_server.createMethod(constants::get_controller_info_method_name);
  get_controller_info_method.attachCallback(callbacks::getControllerInfoCallback);
  get_controller_info_method.setReturnTypeObject();

  ModularDevice::Method& move_method = globals::modular_server.createMethod(constants::move_method_name);
  move_method.attachCallback(callbacks::moveCallback);

  ModularDevice::Method& play_tone_method = globals::modular_server.createMethod(constants::play_tone_method_name);
  play_tone_method.attachCallback(callbacks::playToneCallback);

  // Setup Streams
  Serial.begin(constants::baudrate);

  // Start Server
  globals::modular_server.startServer();
}

void Controller::update()
{
  globals::modular_server.handleServerRequests();
}

void Controller::motorDriveUpdate()
{
  motor_drive_.update();
}

void Controller::handleMotionInterrupt()
{
  if (!isEnabled())
  {
    enable();
  }
  // constants::ModeType mode;
  // globals::modular_server.getFieldValue(constants::mode_name,mode);
  // if (mode == constants::WAYPOINT)
  if (true)
  {
    bool waypoint_repeat;
    globals::modular_server.getFieldValue(constants::waypoint_repeat_field_name,waypoint_repeat);
    if (!waypoint_repeat)
    {
      goToNextWaypoint();
    }
    else if (!waypoint_repeating_)
    {
      startWaypointRepeat();
    }
    else
    {
      stopWaypointRepeat();
    }
  }
}

void Controller::enable()
{
  motor_drive_.enable();
}

void Controller::disable()
{
  motor_drive_.disable();
}

bool Controller::isEnabled()
{
  return motor_drive_.isEnabled();
}

void Controller::stop()
{
  stopWaypointRepeat();
  motor_drive_.stopAll();
}

void Controller::move()
{
  if (!isEnabled())
  {
    enable();
  }
  // constants::ModeType mode;
  // globals::modular_server.getFieldValue(constants::mode_name,mode);
  // if (mode == constants::WAYPOINT)
  if (true)
  {
    bool waypoint_repeat;
    globals::modular_server.getFieldValue(constants::waypoint_repeat_field_name,waypoint_repeat);
    if (!waypoint_repeat)
    {
      goToNextWaypoint();
    }
    else
    {
      startWaypointRepeat();
    }
  }
}

Array<bool,constants::MOTOR_COUNT> Controller::isRunning()
{
  return motor_drive_.isRunningAll();
}

Array<long,constants::MOTOR_COUNT> Controller::getCurrentPosition()
{
  return motor_drive_.getCurrentPositionAll();
}

Array<long,constants::MOTOR_COUNT> Controller::getTargetPosition()
{
  return motor_drive_.getTargetPositionAll();
}

void Controller::playTone()
{
  long tone_frequency;
  globals::modular_server.getFieldValue(constants::tone_frequency_field_name,tone_frequency);

  long tone_duration;
  globals::modular_server.getFieldValue(constants::tone_duration_field_name,tone_duration);

  tone(constants::speaker_pin,tone_frequency,tone_duration);
}

void Controller::goToNextWaypoint()
{
  bool play_tone_before_move;
  globals::modular_server.getFieldValue(constants::play_tone_before_move_field_name,play_tone_before_move);
  if (play_tone_before_move)
  {
    playTone();
  }
  motor_drive_.goToNextWaypoint(0);
}

void Controller::setWaypointCount()
{
  motor_drive_.stopAll();
  motor_drive_.zeroAll();
  motor_drive_.setSpeed();
}

void Controller::setWaypointTravelDuration()
{
  motor_drive_.stopAll();
  motor_drive_.zeroAll();
  motor_drive_.setSpeed();
}

void Controller::startWaypointRepeat()
{
  if (!waypoint_repeating_)
  {
    waypoint_repeating_ = true;
    long waypoint_repeat_period;
    globals::modular_server.getFieldValue(constants::waypoint_repeat_period_field_name,waypoint_repeat_period);
    waypoint_repeat_event_id_ = EventController::event_controller.addInfiniteRecurringEventUsingDelay(callbacks::waypointRepeatCallback,0,waypoint_repeat_period);
  }
}

void Controller::stopWaypointRepeat()
{
  if (waypoint_repeating_)
  {
    waypoint_repeating_ = false;
    EventController::event_controller.removeEvent(waypoint_repeat_event_id_);
  }
}

void Controller::attachMotionInterrupts()
{
  pinMode(constants::motion_switch_interrupt_pin, INPUT);
  digitalWrite(constants::motion_switch_interrupt_pin, HIGH);
  int motion_switch_interrupt_mode = constants::motion_switch_interrupt_mode_default;
  attachInterrupt(constants::motion_switch_interrupt_number,callbacks::motionCallback,motion_switch_interrupt_mode);

  pinMode(constants::motion_bnc_interrupt_pin, INPUT);
  digitalWrite(constants::motion_bnc_interrupt_pin, HIGH);
  int motion_bnc_interrupt_mode = constants::motion_bnc_interrupt_mode_default;
  attachInterrupt(constants::motion_bnc_interrupt_number,callbacks::motionCallback,motion_bnc_interrupt_mode);
}

void Controller::attachSoundInterrupts()
{
  pinMode(constants::sound_switch_interrupt_pin, INPUT);
  digitalWrite(constants::sound_switch_interrupt_pin, HIGH);
  int sound_switch_interrupt_mode = constants::sound_switch_interrupt_mode_default;
  attachInterrupt(constants::sound_switch_interrupt_number,callbacks::soundCallback,sound_switch_interrupt_mode);

  pinMode(constants::sound_bnc_interrupt_pin, INPUT);
  digitalWrite(constants::sound_bnc_interrupt_pin, HIGH);
  int sound_bnc_interrupt_mode = constants::sound_bnc_interrupt_mode_default;
  attachInterrupt(constants::sound_bnc_interrupt_number,callbacks::soundCallback,sound_bnc_interrupt_mode);
}

Controller controller;
