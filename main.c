/**
  ******************************************************************************
  * @file    main.c 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    19-September-2011
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "usbd_hid_core.h"
#include "usbd_usr.h"
#include "usbd_desc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"


/** @addtogroup STM32F4-Discovery_USB_HID
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/


/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

#ifdef USB_OTG_HS_INTERNAL_DMA_ENABLED
  #if defined ( __ICCARM__ ) /*!< IAR Compiler */
    #pragma data_alignment = 4   
  #endif
#endif /* USB_OTG_HS_INTERNAL_DMA_ENABLED */
__ALIGN_BEGIN USB_OTG_CORE_HANDLE  USB_OTG_dev __ALIGN_END;

__IO uint8_t UserButtonPressed = 0x00;
uint8_t InBuffer[64], OutBuffer[63], Buf[63];

/* Private function prototypes -----------------------------------------------*/
void Delayms(__IO uint32_t nCount);
void SendStrToUSB(uint8_t* str);
void ClearBuffer(void);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */

int main(void)
{
  STM32F4_Discovery_LEDInit(LED3);
  STM32F4_Discovery_LEDInit(LED4);
  STM32F4_Discovery_LEDInit(LED5);
  STM32F4_Discovery_LEDInit(LED6);
  STM32F4_Discovery_PBInit(BUTTON_USER, BUTTON_MODE_GPIO);

  USBD_Init(&USB_OTG_dev,
#ifdef USE_USB_OTG_HS
  USB_OTG_HS_CORE_ID,
#else
  USB_OTG_FS_CORE_ID,
#endif
  &USR_desc,
  &USBD_HID_cb,
  &USR_cb);

  STM32F4_Discovery_LEDInit(LED3);
  STM32F4_Discovery_LEDInit(LED4);
  STM32F4_Discovery_LEDInit(LED5);
  STM32F4_Discovery_LEDInit(LED6);

  while (1)
  {
	  Delayms(0xFFFF);

		uint32_t i=0,y=0;

		  while (i<64)
		  {
			  Buf[i]=OutBuffer[i];
			  i++;
		  }

		  y=0;

		if (Buf[0] == 't' && Buf[1] == 'e' && Buf[2] == 's' && Buf[3] == 't')
		{

		  SendStrToUSB("Testing 1 2 3 . . .");
		  SendStrToUSB("|||||||||");
		}

		if (Buf[0] == 'l' && Buf[1] == 'e' && Buf[2] == 'd')
		{
			if (Buf[3] == 0x33)
			{
				STM32F4_Discovery_LEDToggle(LED3);
				SendStrToUSB("LED3(Orange) has been toggled!");
				SendStrToUSB("|||||||||");
			}
			if (Buf[3] == 0x34)
			{
				STM32F4_Discovery_LEDToggle(LED4);
				SendStrToUSB("LED4(Green) has been toggled!");
				SendStrToUSB("|||||||||");
			}
			if (Buf[3] == 0x35)
			{
				STM32F4_Discovery_LEDToggle(LED5);
				SendStrToUSB("LED5(Red) has been toggled!");
				SendStrToUSB("|||||||||");
			}
			if (Buf[3] == 0x36)
			{
				STM32F4_Discovery_LEDToggle(LED6);
				SendStrToUSB("LED6(Blue) has been toggled!");
				SendStrToUSB("|||||||||");
			}
		}

		ClearBuffer();
  }
}

void SendStrToUSB(uint8_t* str)
{
	int i=0;
	while (*str)
	{
		InBuffer[i]=*str;
		i++;
		*str++;
	}
	USBD_HID_SendReport(&USB_OTG_dev, InBuffer, i);
}

void ClearBuffer(void)
{
	int i=0;
	while (i<64)
	{
		Buf[i]=0;
		OutBuffer[i]=0;
		i++;
	}
}

/**
  * @brief  Delay Function.
  * @param  nCount:specifies the Delay time length.
  * @retval None
  */
void Delayms(__IO uint32_t nCount)
{
  uint32_t count = 0;
  const uint32_t utime = (120 * nCount / 7);
  do
  {
    if ( ++count > utime )
    {
      return ;
    }
  }
  while (1);
}

/**
  * @brief  Inserts a delay time.
  * @param  nTime: specifies the delay time length.
  * @retval None
  */
void Delay(__IO uint32_t nTime)
{
  if (nTime != 0x00)
  { 
    nTime--;
  }
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

/**
  * @}
  */


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
