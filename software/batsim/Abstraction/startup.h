
#ifndef STARTUP_H_
#define STARTUP_H_

#include "display.h"
#include "buttons.h"

#ifdef __cplusplus
extern "C"
{
#endif

void startup_Hardware(void);
void startup_Software(void);

#ifdef __cplusplus
}
#endif

#endif
