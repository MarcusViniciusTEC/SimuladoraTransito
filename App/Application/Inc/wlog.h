#ifndef __WLOG_H__
#define __WLOG_H__

/******************************************************************************/

#include "sl.h"

/******************************************************************************/

extern volatile uint32_t wlog_execution_rate_1ms_timer;

#define wlog_pexecution_rate_1ms_timer 	            (&wlog_execution_rate_1ms_timer)

#define WLOG_EXECUTION_RATE_1MS_TIME    	        0

/******************************************************************************/

#define WLOG_TX_START_TRANSMISSION_DELAY_1MS_TIME   4

/******************************************************************************/

extern void wlog_tx(uint8_t token);

/******************************************************************************/

void wlog_1ms_clock(void);
void wlog_init(void);
void wlog_update(void);
void wlog_deinit(void);

/******************************************************************************/

void wlog_tx_next(void);
void wlog_rx(uint8_t token);

/******************************************************************************/

static const char *const get_confirmation_string[] =
{
	[NO] 	= ( "N" ),
	[YES] 	= ( "S"),
};

/******************************************************************************/

static const char *const get_status_string[] =
{
	[NOK] 	= ( "NOK" ),
	[OK] 	= ( "OK"),
};

/******************************************************************************/

static const char *const get_onoff_state_string[] =
{
	[OFF] 	= ( "OFF" ),
	[ON] 	= ( "ON"),
};

/******************************************************************************/

#endif/*__WLOG_H__*/
