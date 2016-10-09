#include <stddef.h>
#include "stm32l1xx.h"

int main(void)
{

	int button,counter;

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

	GPIO_InitTypeDef gpioInitStruct;
	gpioInitStruct.GPIO_Mode=GPIO_Mode_OUT;
	gpioInitStruct.GPIO_OType=GPIO_OType_PP;
	gpioInitStruct.GPIO_Pin=GPIO_Pin_5;
	gpioInitStruct.GPIO_Speed=GPIO_Speed_40MHz;

	GPIO_Init(GPIOA, &gpioInitStruct);

	GPIO_SetBits(GPIOA,GPIO_Pin_5);

	gpioInitStruct.GPIO_Mode=GPIO_Mode_IN;
	gpioInitStruct.GPIO_PuPd=GPIO_PuPd_UP;
	gpioInitStruct.GPIO_Pin=GPIO_Pin_13;
	gpioInitStruct.GPIO_Speed=GPIO_Speed_40MHz;

	GPIO_Init(GPIOC, &gpioInitStruct);

	uint8_t buttonState = GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13);

    while (1)
    {
    	buttonState = GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13);

    	if(buttonState == 0){
    	    counter=0;
    	    button=0;
    	    while(1){
    	    	if(buttonState == 1){
    	    		while(1){
    	    			if(counter>1000){
    	    				if(buttonState == 0){
    	    					GPIO_ToggleBits(GPIOA,GPIO_Pin_5);
    	    					button=1;
    	    					break;
    	    				}
    	    			}
    	    			counter++;
    	    		}
    	    		if(button == 1)
    	    			break;
    	    	}
    	    }
    	}

    }
    return 0;
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/*
 * Minimal __assert_func used by the assert() macro
 * */
void __assert_func(const char *file, int line, const char *func, const char *failedexpr)
{
  while(1)
  {}
}

/*
 * Minimal __assert() uses __assert__func()
 * */
void __assert(const char *file, int line, const char *failedexpr)
{
   __assert_func (file, line, NULL, failedexpr);
}
