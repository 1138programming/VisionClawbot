#include "main.h"

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
	pros::Controller master(pros::E_CONTROLLER_MASTER);
	// pros::Motor left_mtr(1);
	pros::Motor base(2);
	pros::Vision vision(1);
	pros::vision_signature_s_t SIG_1 = {1, {1, 0, 0}, 9.300000, -3689, -3011, -3350, 11241, 12827, 12034, 0, 0};
	pros::vision_signature_s_t SIG_2 = {2, {1, 0, 0}, 4.000000, 7357, 9315, 8336, -1041, -441, -741, 0, 0};
	pros::vision_signature_s_t SIG_3 = {3, {1, 0, 0}, 1.400000, -2809, -2395, -2602, -6057, -5689, -5873, 0, 0};

	while (true) {
		
		pros::lcd::print(0, "%d %d %d",
						 (pros::lcd::read_buttons() & LCD_BTN_LEFT) >> 2,
		                 (pros::lcd::read_buttons() & LCD_BTN_CENTER) >> 1,
		                 (pros::lcd::read_buttons() & LCD_BTN_RIGHT) >> 0);
		vision.set_signature(1, &SIG_1);
		vision.set_signature(2, &SIG_2);
		vision.set_signature(3, &SIG_3);

		//std::cout << "Number of Objects Detected: " << vision.get_object_count() << "\n";
		pros::vision_object_s_t SIG1 = vision.get_by_sig(0, 1);
		pros::vision_object_s_t SIG2 = vision.get_by_sig(0, 2);
		pros::vision_object_s_t SIG3 = vision.get_by_sig(0, 3);

		if (SIG1.y_middle_coord <= 5 && SIG1.y_middle_coord >= -5)
		{
			printf("Stopping\n");
			base.move_velocity(0);
			printf("%d" SIG1.y_middle_coord);
		}
		else if (SIG2.y_middle_coord <= 5 && SIG2.y_middle_coord >= -5)
		{
			printf("Stopping SIG2\n");
			base.move_velocity(0);
			printf("%d" SIG2.y_middle_coord);
		}
		else if (SIG1.y_middle_coord > 5)
		{
			printf("Moving right.\n");
			base.move_velocity(20);
			printf("%d" SIG1.y_middle_coord);
		}
		else if (SIG1.y_middle_coord < 5)
		{
			printf("Moving left.\n");
			base.move_velocity(-20);
			printf("%d" SIG1.y_middle_coord);
		}
		else if (SIG2.y_middle_coord > 5)
		{
			printf("Moving right.\n");
			base.move_velocity(20);
			printf("%d" SIG2.y_middle_coord);
		}
		else if (SIG2.y_middle_coord < 5)
		{
			printf("Moving left.\n");
			base.move_velocity(-20);
			printf("%d" SIG2.y_middle_coord);
		}
		else 
		{
			printf("Moving\n");
			base.move_velocity(20);
			printf("%d" SIG1.y_middle_coord);
		}
	}
}
