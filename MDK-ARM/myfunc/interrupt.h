#ifndef _INTERRUPT_H_
#define _INTERRUPT_H_
#include "main.h"
#include "stdbool.h"
#define LONGSHOT 50
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
struct keys{
	/*bool sta;
	uint8_t dcnt , ucnt , Flag , rep , repcnt;*/
	bool sta;
	uint8_t state , event , press_cnt , multi_cnt , click_cnt , long_flag , bounce_cnt , discnt;    // ????????
};
extern struct keys key[4];
#endif