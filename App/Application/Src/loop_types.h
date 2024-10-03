#ifndef __LOOP_TYPES_H__
#define __LOOP_TYPES_H__


#include "loop_cfg.h"

typedef struct
{
  GPIO_TypeDef *GPIO;
      uint32_t  PinMask;
} loop_pininfo_t;


#endif