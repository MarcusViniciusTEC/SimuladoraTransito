#include "sl.h"
#include "hmi.h"
#include "hmi_cfg.h"
//#include "app_cfg.h"

/******************************************************************************/

//#include "wlog.h"

/******************************************************************************/

volatile uint32_t hmi_execution_rate_1ms_timer;

/******************************************************************************/

static volatile hmi_data_t hmi_data;

/******************************************************************************/

static const hmi_pininfo_t hmi_led_pininfo_vector[HMI_NUMBER_OF_LEDS] = hmi_led_pininfo_vector_default_value;

/******************************************************************************/

static void hmi_turn_on_led_pin(uint8_t led_index)
{
  hmi_pininfo_t led_pininfo;

  led_pininfo = hmi_led_pininfo_vector[led_index];
  LL_GPIO_SetOutputPin(led_pininfo.GPIO, led_pininfo.PinMask);
}

/******************************************************************************/

static void hmi_turn_off_led_pin(uint8_t led_index)
{
  hmi_pininfo_t led_pininfo;

  led_pininfo = hmi_led_pininfo_vector[led_index];
  LL_GPIO_ResetOutputPin(led_pininfo.GPIO, led_pininfo.PinMask);
}

/******************************************************************************/

void hmi_led_turn_on(uint8_t led_index)
{
  hmi_turn_on_led_pin(led_index);
  LED_ON(hmi_data.led.next_mask, led_index);
}

/******************************************************************************/

void hmi_led_turn_off(uint8_t led_index)
{
  hmi_turn_off_led_pin(led_index);
  LED_OFF(hmi_data.led.next_mask, led_index);
}

/******************************************************************************/

void hmi_led_toggle(uint8_t led_index)
{
  LED_TOGGLE(hmi_data.led.next_mask, led_index);
}

/******************************************************************************/

void hmi_led_blink(uint8_t led_index, hmi_blnk_auto_restart_t blnk_auto_restart)
{
  hmi_led_turn_on(led_index);
  hmi_data.blnk[led_index].led_1ms_timer = HMI_BLNK_ON_1MS_TIME;
  hmi_data.blnk[led_index].cycles = HMI_PULSE_NUMBER_OF_CYCLES;
  hmi_data.blnk[led_index].state = HMI_BLNK_STATE_ON;
  hmi_data.blnk[led_index].led_blnk_auto_restart = blnk_auto_restart;
}

/******************************************************************************/

void hmi_led_short_pulse(uint8_t led_index, hmi_blnk_auto_restart_t blnk_auto_restart)
{
  hmi_led_turn_on(led_index);
  hmi_data.blnk[led_index].led_1ms_timer = HMI_SHORT_PULSE_ON_1MS_TIME;
  hmi_data.blnk[led_index].cycles = HMI_PULSE_NUMBER_OF_CYCLES;
  hmi_data.blnk[led_index].state = HMI_SHORT_PULSE_STATE_ON;
  hmi_data.blnk[led_index].led_blnk_auto_restart = blnk_auto_restart;
}

/******************************************************************************/

void hmi_led_long_pulse(uint8_t led_index, hmi_blnk_auto_restart_t blnk_auto_restart)
{
  hmi_led_turn_on(led_index);
  hmi_data.blnk[led_index].led_1ms_timer = HMI_LONG_PULSE_ON_1MS_TIME;
  hmi_data.blnk[led_index].cycles = HMI_PULSE_NUMBER_OF_CYCLES;
  hmi_data.blnk[led_index].state = HMI_LONG_PULSE_STATE_ON;
  hmi_data.blnk[led_index].led_blnk_auto_restart = blnk_auto_restart;
}

/******************************************************************************/

//static void hmi_blnk_turn_leds_on(void)
//{
//  for(uint8_t led_index = 0; led_index < HMI_NUMBER_OF_LEDS; led_index++)
//  {
//    hmi_led_turn_on(led_index);
//  }
//}

/******************************************************************************/

static void hmi_blnk_turn_leds_off(void)
{
  for(uint8_t led_index = 0; led_index < HMI_NUMBER_OF_LEDS; led_index++)
  {
	  hmi_led_turn_off(led_index);
  }
}

/******************************************************************************/

static hmi_blnk_state_t hmi_blnk_get_state(uint8_t led_index)
{
  hmi_blnk_state_t blnk_state;
  sl_critical_assign(blnk_state, hmi_data.blnk[led_index].state);
  return blnk_state;
}

/******************************************************************************/
/******************************************************************************/

static void hmi_blnk_1ms_clock(void)
{
  for(uint8_t led_index = 0; led_index < HMI_NUMBER_OF_LEDS; led_index++)
  {
    if(hmi_data.blnk[led_index].led_1ms_timer > 0)
    {
      hmi_data.blnk[led_index].led_1ms_timer--;
    }
  }
}

/******************************************************************************/

static void hmi_blnk_heartbeat_led(void)
{
  //hmi_led_blink(APP_HEARTBEAT_LED_A_INDEX, HMI_BLNK_AUTO_RESTART_ON);
}

/******************************************************************************/

static void hmi_blnk_init(void)
{
  for(uint8_t led_index = 0; led_index < HMI_NUMBER_OF_LEDS; led_index++)
  {
	hmi_led_short_pulse(led_index, HMI_BLNK_AUTO_RESTART_OFF);
    hmi_data.blnk[led_index].cycles = HMI_INIT_BLNK_NUMBER_OF_CYCLES;
  }
}

/******************************************************************************/

static void hmi_blnk_update_state(uint8_t led_index, hmi_blnk_state_t blnk_state, uint32_t led_1ms_timer)
{
  if(blnk_state == HMI_SHORT_PULSE_STATE_OFF || blnk_state == HMI_LONG_PULSE_STATE_OFF || blnk_state == HMI_BLNK_STATE_OFF)
  {
    hmi_led_turn_off(led_index);
    sl_critical_assign(hmi_data.blnk[led_index].led_1ms_timer, led_1ms_timer);
    hmi_data.blnk[led_index].state = blnk_state;
  }
  else if(blnk_state == HMI_SHORT_PULSE_STATE_ON || blnk_state == HMI_LONG_PULSE_STATE_ON || blnk_state == HMI_BLNK_STATE_ON)
  {
	if(hmi_data.blnk[led_index].led_blnk_auto_restart == HMI_BLNK_AUTO_RESTART_OFF)
	{
	  hmi_data.blnk[led_index].cycles--;
	  if(hmi_data.blnk[led_index].cycles == 0)
	  {
		hmi_led_turn_off(led_index);
		hmi_data.blnk[led_index].state = HMI_BLNK_STATE_DONE;
	  }
	  else
	  {
		hmi_led_turn_on(led_index);
        sl_critical_assign(hmi_data.blnk[led_index].led_1ms_timer, led_1ms_timer);
		hmi_data.blnk[led_index].state = blnk_state;
	  }
	}
	else
	{
	  hmi_led_turn_on(led_index);
	  sl_critical_assign(hmi_data.blnk[led_index].led_1ms_timer, led_1ms_timer);
	  hmi_data.blnk[led_index].state = blnk_state;

      //if (led_index == (uint8_t)APP_HEARTBEAT_LED_A_INDEX)
      {
       // wlog(".");
      }
	}
  }
}

/******************************************************************************/

static void hmi_blnk_update(uint8_t led_index)
{
  uint32_t led_1ms_timer;

  sl_critical_assign(led_1ms_timer, hmi_data.blnk[led_index].led_1ms_timer);
  if(led_1ms_timer == 0)
  {
    switch(hmi_data.blnk[led_index].state)
    {
      case HMI_SHORT_PULSE_STATE_OFF:
  	    hmi_blnk_update_state(led_index, HMI_SHORT_PULSE_STATE_ON, HMI_SHORT_PULSE_ON_1MS_TIME);
        break;
      case HMI_LONG_PULSE_STATE_OFF:
        hmi_blnk_update_state(led_index, HMI_LONG_PULSE_STATE_ON, HMI_LONG_PULSE_ON_1MS_TIME);
        break;
      case HMI_BLNK_STATE_OFF:
        hmi_blnk_update_state(led_index, HMI_BLNK_STATE_ON, HMI_BLNK_ON_1MS_TIME);
        break;

      case HMI_SHORT_PULSE_STATE_ON:
        hmi_blnk_update_state(led_index, HMI_SHORT_PULSE_STATE_OFF, HMI_SHORT_PULSE_OFF_1MS_TIME);
        break;
      case HMI_LONG_PULSE_STATE_ON:
        hmi_blnk_update_state(led_index, HMI_LONG_PULSE_STATE_OFF, HMI_LONG_PULSE_OFF_1MS_TIME);
        break;
      case HMI_BLNK_STATE_ON:
        hmi_blnk_update_state(led_index, HMI_BLNK_STATE_OFF, HMI_BLNK_OFF_1MS_TIME);
        break;

      case HMI_BLNK_STATE_DONE:
        break;

      default:
        break;
    }
  }
}

/******************************************************************************/

static void hmi_blnk_deinit(void)
{
  hmi_blnk_turn_leds_off();
}

/******************************************************************************/

static void hmi_led_1ms_clock(void)
{
}

/******************************************************************************/

static void hmi_led_init(void)
{
  hmi_data.led.mask = 0;
  hmi_data.led.next_mask = 0;
}

/******************************************************************************/

static void hmi_led_update(uint32_t next_mask)
{
  for(uint8_t led_index = 0; led_index < HMI_NUMBER_OF_LEDS; led_index++)
  {
	hmi_blnk_update(led_index);
  //hmi_blnk_update();

    uint32_t led_mask = (uint32_t)( 1 << led_index );
    if((hmi_data.led.mask ^ next_mask) & led_mask)
    {
	  if((next_mask & led_mask) == 0)
	  {
	    hmi_turn_off_led_pin(led_index);
	  }
	  else
	  {
	    hmi_turn_on_led_pin(led_index);
	  }
    }
  }
}

/******************************************************************************/

static void hmi_led_deinit(void)
{
}

/******************************************************************************/

void hmi_1ms_clock(void)
{
  switch(hmi_data.state)
  {
    case HMI_STATE_INIT:
      hmi_blnk_1ms_clock();
      break;
    case HMI_STATE_RUNNING:
      hmi_blnk_1ms_clock();
      hmi_led_1ms_clock();
      break;
    default:
      break;
  }
}


/******************************************************************************/

void hmi_init(void)
{
 // hmi_blnk_init();
  hmi_led_init();

  hmi_data.state = HMI_STATE_INIT;
}

/******************************************************************************/

void hmi_update(void)
{
  uint32_t next_mask;

  next_mask = hmi_data.led.next_mask;
  hmi_led_update(next_mask);

  switch(hmi_data.state)
  {
    case HMI_STATE_INIT:
	  if(hmi_blnk_get_state(HMI_NUMBER_OF_LEDS - 1) == HMI_BLNK_STATE_DONE)
	  {
		hmi_blnk_turn_leds_off();
		hmi_blnk_heartbeat_led();
		hmi_data.state = HMI_STATE_RUNNING;
	  }
	  break;

    case HMI_STATE_RUNNING:
	  break;

    default:
	  break;
  }

  if(next_mask != hmi_data.led.mask)
  {
	hmi_data.led.mask = next_mask;
  }
}

/******************************************************************************/

void hmi_deinit(void)
{
  switch(hmi_data.state)
  {
  case HMI_STATE_INIT:
    hmi_blnk_deinit();
  break;
  case HMI_STATE_RUNNING:
    hmi_led_deinit();
  break;
  default:
  break;
  }
}

/******************************************************************************/
