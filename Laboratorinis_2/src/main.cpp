#include <stm32f4xx_hal.h>
#include <iostream>
#ifdef _cplusplus
extern "C"
#endif

void SysTick_Handler(void){
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();

}

static TIM_HandleTypeDef s_TimerInstance = {.Instance = TIM4};

void InitializeTimer(){
	__TIM4_CLK_ENABLE();
	s_TimerInstance.Init.Prescaler = 400;
	s_TimerInstance.Init.CounterMode = TIM_COUNTERMODE_UP;
	s_TimerInstance.Init.Period = 500;
	s_TimerInstance.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	s_TimerInstance.Init.RepetitionCounter = 0;
	HAL_TIM_Base_Init(&s_TimerInstance);
	HAL_TIM_Base_Start(&s_TimerInstance);

}

void InitializeLED(){

	__GPIOD_CLK_ENABLE();
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.Pin = GPIO_PIN_13;
	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStructure.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStructure);

}

int main (void){
	HAL_Init();
	InitializeLED();
	InitializeTimer();


for (;;) {
	int timerValue = __HAL_TIM_GET_COUNTER(&s_TimerInstance);
	if(timerValue == 100){HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_SET);};
	if(timerValue == 500){HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_RESET);};
}

}

