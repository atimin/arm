#include "pc_control.h"
#include "servo.h" 

CMD_Status_t exec_command(const char* cmd)
{
  CMD_Status_t status = CMD_OK;
  int serv = -1;
  float angle = -1;
  float velocity = -1;
  sscanf(cmd, "[SERV=%i ANGLE=%f VEL=%f]", &serv, &angle, &velocity);

  if (serv >= 0 && serv < 6)
    if (angle >= 0 && angle <= M_PI/2)
      if (velocity > 0) 
        Servo_SetAngle(serv, angle, velocity);
  else status = VEL_ERROR;
  else status = ANGLE_ERROR;
  else status = NUM_SERVO_ERROR;
  return status;
}
