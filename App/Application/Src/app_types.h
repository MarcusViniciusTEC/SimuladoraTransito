#ifndef __APP_TYPES_H__
#define __APP_TYPES_H__

/******************************************************************************/

typedef enum
{
  APP_STATE_ = 0,
  APP_NUMBER_OF_STATES
} app_state_t;

/******************************************************************************/

typedef enum
{
  APP_MB_REG_INDEX_BOARD_MODEL = 0,
  APP_MB_REG_INDEX_BOARD_SERIAL_NUMBER_0,
  APP_MB_REG_INDEX_BOARD_SERIAL_NUMBER_1,
  APP_MB_REG_INDEX_BOARD_SERIAL_NUMBER_2,
  APP_MB_REG_INDEX_BOARD_FIRMWARE_MAJOR,
  APP_MB_REG_INDEX_BOARD_FIRMWARE_MINOR,
  APP_MB_REG_INDEX_BOARD_TEMPERATURE,
  APP_MB_REG_INDEX_GPIN,
  APP_MB_REG_INDEX_GPOUT,
  APP_MB_NUMBER_OF_REG_INDEXES
} app_mb_reg_index_t;

/******************************************************************************/

typedef struct
{
  uint16_t reg_vector[APP_MB_NUMBER_OF_REG_INDEXES];
  uint32_t valid_message_received_1ms_timer;
  uint32_t invalid_message_received_1ms_timer;
} app_mb_data_t;

/******************************************************************************/

typedef struct
{
  uint32_t update_cycle_1ms_timer;
} app_tmp_data_t;

/******************************************************************************/

// typedef struct
// {
// } app_din_data_t;

/******************************************************************************/

typedef struct
{
  uint16_t state_mask;
} app_dout_data_t;

/******************************************************************************/

typedef struct
{
     app_state_t state;

    app_mb_data_t mb;
   app_tmp_data_t tmp;
   //app_din_data_t din;
   app_dout_data_t dout;
} app_data_t;

/******************************************************************************/

#endif/*__APP_TYPES_H__*/
