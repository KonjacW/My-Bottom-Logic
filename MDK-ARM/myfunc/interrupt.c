#include "interrupt.h"
#include "lcd.h"


struct keys key[4] = {0,0,0,0};
int endflag = 0;
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	if(htim->Instance == TIM3){
		key[0].sta = !HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_0);
		key[1].sta = !HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_1);
		key[2].sta = !HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_2);
		key[3].sta = !HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0);
		
		for(int i = 0;i<4;++i){
			if(key[i].state == 0){
				if(key[i].sta){
					key[i].state = 1;
					key[i].press_cnt = 0;
				}
			}
			else if(key[i].state == 1){
				if(!key[i].sta)key[i].state = 0 , key[i].press_cnt = 0;
				else{
					key[i].press_cnt ++;
					if(key[i].press_cnt >= 5)
						key[i].state = 2 , key[i].press_cnt = 0 , key[i].long_flag = 0;
				}
			}
			else if(key[i].state == 2){
				if(key[i].sta){
					key[i].press_cnt ++;
					if(!key[i].long_flag && key[i].press_cnt >= 30)key[i].long_flag = 1 , key[i].event = 2;
				}else{
					key[i].bounce_cnt = 0;
					key[i].state = 3;
				}
			}
			else if(key[i].state == 3){
				if(!key[i].sta){
					key[i].bounce_cnt ++;
					if(key[i].bounce_cnt >= 5)
						if(!key[i].long_flag){
							key[i].click_cnt ++;
							key[i].multi_cnt = 0;
							key[i].state = 4;
						}else{
							key[i].long_flag = 0;
							key[i].state = 0;//1 or 2
						}
				}else key[i].bounce_cnt = 0 , key[i].press_cnt = 0;// , key[i].long_flag = 0;
			}
			else if(key[i].state == 4){
				key[i].multi_cnt ++;
				if(key[i].sta){
					key[i].press_cnt = 0;
					key[i].state = 1;
				}
				else if(key[i].multi_cnt >= 10){
					if(key[i].click_cnt==1)key[i].event = 1;
					else key[i].event = 3;
					key[i].multi_cnt = 0;
					key[i].state = 0;
					key[i].discnt = key[i].click_cnt;
					key[i].click_cnt = 0;
					key[i].press_cnt = 0;
					key[i].bounce_cnt = 0;
				}
			}
		}
	}
}/*
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	if(htim->Instance == TIM3){
		key[0].sta = !HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_0);
		key[1].sta = !HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_1);
		key[2].sta = !HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_2);
		key[3].sta = !HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0);
		
		for(int i = 0;i<4;++i){
			if(key[i].Flag == -1)
				if(key[i].sta)continue;
				else key[i].Flag = 0;
			if(key[i].rep)key[i].repcnt ++;
			if(key[i].sta){
				key[i].ucnt = 0;
				key[i].dcnt ++;
			}
			else{
				key[i].ucnt ++;
				if(key[i].ucnt <= 2)continue;
				if(key[i].dcnt>=50){
					key[i].Flag = -1;
					key[i].dcnt = 0;
					key[i].repcnt = 0;
					key[i].rep = 0;
				}
				else if(key[i].dcnt<=2)key[i].dcnt = 0;
				else{
					key[i].rep ++;
					key[i].dcnt = 0;
					if(key[i].repcnt >50){
						key[i].Flag = key[i].rep;
						key[i].rep = 0;
						key[i].repcnt = 0;
					}
				}
			}
		}
	}
}*/