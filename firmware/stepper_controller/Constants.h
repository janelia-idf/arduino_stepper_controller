// ----------------------------------------------------------------------------
// Constants.h
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#ifndef CONSTANTS_H
#define CONSTANTS_H
#include "ConstantVariable.h"


namespace constants
{
//MAX values must be >= 1, >= created/copied count, < RAM limit
enum{FIELD_COUNT_MAX=10};
enum{PARAMETER_COUNT_MAX=1};
enum{METHOD_COUNT_MAX=6};

enum ModeType {WAYPOINT};
enum {MOTOR_COUNT=1};

extern const size_t baudrate;

extern const size_t model_number;

extern const long firmware_major;
extern const long firmware_minor;
extern const long firmware_patch;

extern const size_t speaker_pin;
extern const size_t drive_enable_pin;
extern const size_t step_pins[MOTOR_COUNT];
extern const size_t dir_pins[MOTOR_COUNT];
extern const size_t motion_switch_interrupt_pin;
extern const size_t sound_switch_interrupt_pin;
extern const size_t motion_bnc_interrupt_pin;
extern const size_t sound_bnc_interrupt_pin;

extern const char orientation_inverted;

extern const int steps_per_rev;

extern const int motion_switch_interrupt_number;
extern const int motion_switch_interrupt_mode_default;
extern const int sound_switch_interrupt_number;
extern const int sound_switch_interrupt_mode_default;

extern const int motion_bnc_interrupt_number;
extern const int motion_bnc_interrupt_mode_default;
extern const int sound_bnc_interrupt_number;
extern const int sound_bnc_interrupt_mode_default;

extern ConstantString device_name;

extern ConstantString duration_parameter_units;
extern ConstantString frequency_parameter_units;

// Fields
// Field values must be long, double, bool, long[], double[], bool[], char[]
// extern ConstantString mode_field_name;
// extern const ModeType mode_default;

extern ConstantString micro_steps_per_step_field_name;
extern const long micro_steps_per_step_min;
extern const long micro_steps_per_step_max;
extern const long micro_steps_per_step_default;

extern ConstantString waypoint_count_field_name;
extern const long waypoint_count_min;
extern const long waypoint_count_max;
extern const long waypoint_count_default;

extern ConstantString waypoint_travel_duration_field_name;
extern const long waypoint_travel_duration_min;
extern const long waypoint_travel_duration_max;
extern const long waypoint_travel_duration_default;

extern ConstantString enable_polarity_high_field_name;
extern const bool enable_polarity_high_default;

extern ConstantString tone_frequency_field_name;
extern const long tone_frequency_min;
extern const long tone_frequency_max;
extern const long tone_frequency_default;

extern ConstantString tone_duration_field_name;
extern const long tone_duration_min;
extern const long tone_duration_max;
extern const long tone_duration_default;

extern ConstantString play_tone_before_move_field_name;
extern const bool play_tone_before_move_default;

extern ConstantString waypoint_repeat_field_name;
extern const bool waypoint_repeat_default;

extern ConstantString waypoint_repeat_period_field_name;
extern const long waypoint_repeat_period_min;
extern const long waypoint_repeat_period_max;
extern const long waypoint_repeat_period_default;

// Parameters

// Methods
extern ConstantString enable_method_name;
extern ConstantString disable_method_name;
extern ConstantString stop_method_name;
extern ConstantString get_controller_info_method_name;
extern ConstantString move_method_name;
extern ConstantString play_tone_method_name;

// Errors
extern ConstantString waypoint_parameter_error;
}
#endif
