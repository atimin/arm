#ifndef _PC_CONTROL_
#define _PC_CONTROL_

#include <stdio.h>
#include <stdint.h>

typedef enum
{
  CMD_OK = 0,
  NUM_SERVO_ERROR,
  ANGLE_ERROR,
  VEL_ERROR
} CMD_Status_t;

extern CMD_Status_t exec_command(const char* cmd);

#endif
