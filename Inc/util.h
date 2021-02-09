/**
 ******************************************************************************
 * @file		util.h
 * @author		WrathWings
 * @version 	V1.0
 * @date		2019.9.24
 * @brief		Header file of util.c
 ******************************************************************************
 * @attention
 *
 ******************************************************************************
 */
 
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __UTIL_H
#define __UTIL_H

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "math.h"

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define	SQRT3			(1.73205080757f)
#define ONE_BY_SQRT3    (0.57735026919f)
#define TWO_BY_SQRT3    (2.0f * 0.57735026919f)
#define SQRT3_BY_2      (0.86602540378f)

#define SQUARE(x)								((x) * (x))
#define MAX(a, b)       						(((a) > (b)) ? (a) : (b))
#define MIN(a, b)       						(((a) < (b)) ? (a) : (b))

/* USER CODE END PD */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private prototypes --------------------------------------------------------*/
/* USER CODE BEGIN Prototypes */

void Saturation_float(float *value, float upLimit, float downLimit);
void Saturation_int(int *value, int upLimit, int downLimit);
void Saturation_uint16(uint16_t *value, uint16_t upLimit, uint16_t downLimit);

/* USER CODE END Prototypes */

#endif

/************************ (C) COPYRIGHT Action *****END OF FILE****/
