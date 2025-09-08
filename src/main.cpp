#include "main.h"
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "ports.h"
#include "pros/misc.h"
#include "pros/misc.hpp"
#include "helpers.cpp" // IWYU pragma: keep

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");

	pros::lcd::register_btn1_cb(on_center_button);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	pros::Controller controller(pros::E_CONTROLLER_MASTER);
	left_motors.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	right_motors.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);

	print_tracking_wheels();

	double deadzone = 7.5; // deadzone for joystick input

	while (true) {
		double fwd = controller.get_analog(ANALOG_LEFT_Y);
        double turn = pow(controller.get_analog(ANALOG_RIGHT_X), 3) / 10000;
        if (fabs(fwd) > deadzone || fabs(turn) > deadzone) {
			left_motors.move(fwd + turn);
			right_motors.move(fwd - turn);
        } else {
            left_motors.brake();
			right_motors.brake();
        }

		// other motor actions soon

		if (controller.get_digital_new_press(DIGITAL_R1)) {
			if (controller.get_digital_new_press(DIGITAL_R2)) {
				intake_top.move(-127);
				intake_bottom.move(127);
			} else {
				intake_top.move(127);
				intake_bottom.move(127);
			}
		} else if (controller.get_digital_new_release(DIGITAL_R1) || controller.get_digital_new_release(DIGITAL_R2)) {
			intake_top.brake();
			intake_bottom.brake();
		}

		pros::delay(20);
	}
}
