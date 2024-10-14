#include "sl.h"
//#include "app.h"

/******************************************************************************/

#include "wlog.h"

/******************************************************************************/

#include <stdio.h>
#include "stdbool.h"
#include <string.h>

/******************************************************************************/

#define LOG_BUFFER_SIZE                     512		// chars
#define INCR_LOG_BUF_INDEX(p)               ( (p < (LOG_BUFFER_SIZE - 1)) ? (p += 1) : (p = 0) )
#define GET_LOG_BUF_DIFF_INDEX(h, t)        ((uint16_t)(LOG_BUFFER_SIZE - ( (h >= t) ? (h - t) : ((LOG_BUFFER_SIZE - t) + h) ) ))

/******************************************************************************/

volatile uint32_t wlog_execution_rate_1ms_timer;

/******************************************************************************/

typedef struct
{
    uint32_t start_transmission_delay_1ms_timer;

    uint8_t hidx;
    uint8_t tidx;
} wlog_ctrl_t;

/******************************************************************************/

static wlog_ctrl_t wlog_ctrl;
static char sLogBuffer[LOG_BUFFER_SIZE] = { 0 };

/******************************************************************************/
/******************************************************************************/

static void wlog_append(char *log, uint16_t size)
{
	if ( size < (GET_LOG_BUF_DIFF_INDEX(wlog_ctrl.hidx, wlog_ctrl.tidx) - 4) )
	{
		for (uint16_t i = 0; i < size; i++)
		{
			sLogBuffer[wlog_ctrl.hidx] = log[i];
			INCR_LOG_BUF_INDEX(wlog_ctrl.hidx);
		}

		sLogBuffer[wlog_ctrl.hidx] = '\r';
		INCR_LOG_BUF_INDEX(wlog_ctrl.hidx);
		sLogBuffer[wlog_ctrl.hidx] = '\n';
		INCR_LOG_BUF_INDEX(wlog_ctrl.hidx);
		sLogBuffer[wlog_ctrl.hidx] = '\0';
		INCR_LOG_BUF_INDEX(wlog_ctrl.hidx);
	}
}

/******************************************************************************/
/******************************************************************************/

void wlog_init(void)
{
    wlog_ctrl.start_transmission_delay_1ms_timer = 0;
}

/******************************************************************************/

void wlog_1ms_clock(void)
{
    if(wlog_ctrl.start_transmission_delay_1ms_timer > 0)
    {
        wlog_ctrl.start_transmission_delay_1ms_timer--;
        if(wlog_ctrl.start_transmission_delay_1ms_timer == 0)
        {
            wlog_tx_next();
        }
    }
}

/******************************************************************************/

void wlog_update(void)
{
    if(wlog_ctrl.start_transmission_delay_1ms_timer == 0)
    {
        wlog_ctrl.start_transmission_delay_1ms_timer = WLOG_TX_START_TRANSMISSION_DELAY_1MS_TIME;
    }
}

/******************************************************************************/

void wlog_deinit(void)
{
}

/******************************************************************************/
/******************************************************************************/

void wlog(const char *format, ...)
{
	va_list args;
	va_start(args, format);

	uint16_t fsz = strlen(format);
	uint16_t asz = sizeof(args);
	uint16_t log_len = (asz + fsz);

	if (log_len < LOG_BUFFER_SIZE)
	{
		char log_buf[LOG_BUFFER_SIZE]/* = { 0 }*/;

		int fmt_result;
		fmt_result = vsnprintf(log_buf/* + log_len*/, LOG_BUFFER_SIZE - log_len, format, args);
		wlog_append(&log_buf[0], fmt_result);
	}

	va_end(args);
}

/******************************************************************************/

void wlog_tx(uint8_t token)
{
  //LL_USART_TransmitData8(USART1, token);
}


/******************************************************************************/

void wlog_tx_next(void)
{
    if (wlog_ctrl.tidx != wlog_ctrl.hidx)
    {
        wlog_tx((uint8_t)sLogBuffer[wlog_ctrl.tidx]);
        INCR_LOG_BUF_INDEX(wlog_ctrl.tidx);
    }
}

/******************************************************************************/

void wlog_rx(uint8_t token)
{
    return;
}

/******************************************************************************/