#include "pc_control.h"
#include "servo.h" 

uint8_t exec_command(const char* cmd, char* respond)
{
  CMD_Status_t status = 0;
  int count_params = 0;
  int serv = -1;
  float angle = -1;
  float velocity = -1;


  // Moving servos by command
  count_params = sscanf(cmd, "MOVE[SERV=%i ANGLE=%f VEL=%f]\n", &serv, &angle, &velocity);
  if (count_params == 3) {
    if (serv >= 0 && serv < 6)
      if (angle >= 0 && angle <= M_PI)
        if (velocity > 0) 
          Servo_SetAngle(serv, angle, velocity);
    else status = VEL_ERROR;
    else status = ANGLE_ERROR;
    else status = NUM_SERVO_ERROR;

    return sprintf(respond, "RESP[STATUS=%i]\n", status);
  }

  // Getting position of a joint
  count_params = 0;
  count_params = sscanf(cmd, "STATUS[SERV=%i]\n", &serv);
  if (count_params == 1) {
    if (serv >= 0 && serv < 6) 
      return sprintf(respond, "RESP[SERV=%i ANGLE=%.3f VEL=%.3f]\n", 
          serv, 
          Servo_GetAngle(serv),
          Servo_GetVelocity(serv));

    else return sprintf(respond, "RESP[STATUS=%i]", NUM_SERVO_ERROR);
  }

  return 0;
}
