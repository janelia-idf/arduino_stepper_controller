// ----------------------------------------------------------------------------
// Constants.cpp
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#include "Constants.h"


namespace constants
{
const size_t baudrate = 9600;

const size_t model_number = 1140;

// Use semantic versioning http://semver.org/
const long firmware_major = 0;
const long firmware_minor = 1;
const long firmware_patch = 0;

const size_t speaker_pin = 46;
const size_t drive_enable_pin = 49;
const size_t step_pins[MOTOR_COUNT] = {53};
const size_t dir_pins[MOTOR_COUNT] = {51};
const size_t motion_switch_interrupt_pin = 2;
const size_t sound_switch_interrupt_pin = 3;
const size_t motion_bnc_interrupt_pin = 21;
const size_t sound_bnc_interrupt_pin = 20;

const char orientation_inverted = '-';

const int steps_per_rev = 200;

const int motion_switch_interrupt_number = 0;
const int motion_switch_interrupt_mode_default = FALLING;
const int sound_switch_interrupt_number = 1;
const int sound_switch_interrupt_mode_default = FALLING;

const int motion_bnc_interrupt_number = 2;
const int motion_bnc_interrupt_mode_default = RISING;
const int sound_bnc_interrupt_number = 3;
const int sound_bnc_interrupt_mode_default = RISING;

CONSTANT_STRING(device_name,"stepper_controller");

CONSTANT_STRING(duration_parameter_units,"ms");
CONSTANT_STRING(frequency_parameter_units,"Hz");

// Fields
// CONSTANT_STRING(mode_field_name,"mode");
// const ModeType mode_default = WAYPOINT;

CONSTANT_STRING(micro_steps_per_step_field_name,"micro_steps_per_step_count");
const long micro_steps_per_step_min = 1;
const long micro_steps_per_step_max = 256;
const long micro_steps_per_step_default = 256;

CONSTANT_STRING(waypoint_count_field_name,"waypoint_count");
const long waypoint_count_min = 1;
const long waypoint_count_max = 255;
const long waypoint_count_default = 30;

CONSTANT_STRING(waypoint_travel_duration_field_name,"waypoint_travel_duration");
const long waypoint_travel_duration_min = 100;
const long waypoint_travel_duration_max = 10000;
const long waypoint_travel_duration_default = 200;

CONSTANT_STRING(reverse_direction_field_name,"reverse_direction");
const bool reverse_direction_default = false;

CONSTANT_STRING(enable_polarity_high_field_name,"enable_polarity_high");
const bool enable_polarity_high_default = true;

CONSTANT_STRING(tone_frequency_field_name,"tone_frequency");
const long tone_frequency_min = 850;
const long tone_frequency_max = 20000;
const long tone_frequency_default = 5000;

CONSTANT_STRING(tone_duration_field_name,"tone_duration");
const long tone_duration_min = 1;
const long tone_duration_max = 10000;
const long tone_duration_default = 250;

CONSTANT_STRING(play_tone_before_move_field_name,"play_tone_before_move");
const bool play_tone_before_move_default = false;

CONSTANT_STRING(waypoint_repeat_field_name,"waypoint_repeat");
const bool waypoint_repeat_default = false;

CONSTANT_STRING(waypoint_repeat_period_field_name,"waypoint_repeat_period");
const long waypoint_repeat_period_min = 100;
const long waypoint_repeat_period_max = 10000;
const long waypoint_repeat_period_default = 1000;

// Parameters

// Methods
CONSTANT_STRING(enable_method_name,"enable");
CONSTANT_STRING(disable_method_name,"disable");
CONSTANT_STRING(stop_method_name,"stop");
CONSTANT_STRING(get_controller_info_method_name,"getControllerInfo");
CONSTANT_STRING(move_method_name,"move");
CONSTANT_STRING(play_tone_method_name,"playTone");

// Errors
CONSTANT_STRING(waypoint_parameter_error,"waypoint_travel_duration cannot be greater than waypoint_repeat_period when waypoint_repeat is true.");
}
