#ifndef __LOOP_CFG_H__
#define __LOOP_CFG_H__

#include "main.h"

#define LOOP_NUMBER_OF_OUTPUTS  4
#define ONE_CYCLE               1
#define LOOP_CH0_AND_CH1    2
#define LOOP_CH2_AND_CH3    4

#define loop_pininfo_vector_default_value \
{                                         \
  {/*LOOP_IN_1*/                          \
    .GPIO    = LP_1_DET_GPIO_Port,        \
    .PinMask = LP_1_DET_Pin,              \
  }                                       \
  ,                                       \
  {/*LOOP_OUT_1*/                         \
    .GPIO    = LP_2_DET_GPIO_Port,        \
    .PinMask = LP_2_DET_Pin,              \
  }                                       \
  ,                                       \
  {/*LOOP_IN_2*/                          \
    .GPIO    = LP_3_DET_GPIO_Port,        \
    .PinMask = LP_3_DET_Pin,              \
  }                                       \
  ,                                       \
  {/*LOOP_OUT_2*/                         \
    .GPIO    = LP_4_DET_GPIO_Port,        \
    .PinMask = LP_4_DET_Pin               \
  }                                       \
}



#endif