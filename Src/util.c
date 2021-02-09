/**
 ******************************************************************************
 * @file		util.c
 * @author		WrathWings
 * @version 	V1.0
 * @date		2019.9.24
 * @brief		Utility functions
 ******************************************************************************
 * @attention
 *
 ******************************************************************************
 */
 
/* Includes ------------------------------------------------------------------*/
#include "util.h"

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN */

void Saturation_float(float *value, float upLimit, float downLimit)
{	
	if(*value >= upLimit)
	{
		*value	= upLimit;
	}
	else if(*value <= downLimit)
	{
		*value = downLimit;
	}
}

void Saturation_int(int *value, int upLimit, int downLimit)
{	
	if(*value >= upLimit)
	{
		*value	= upLimit;
	}
	else if(*value <= downLimit)
	{
		*value = downLimit;
	}
}

void Saturation_uint16(uint16_t *value, uint16_t upLimit, uint16_t downLimit)
{	
	if(*value >= upLimit)
	{
		*value	= upLimit;
	}
	else if(*value <= downLimit)
	{
		*value = downLimit;
	}
}

/* USER CODE END */



/************************ (C) COPYRIGHT Action *****END OF FILE****/
