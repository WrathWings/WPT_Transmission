/**
 ******************************************************************************
 * @file		WPT_Tx.h
 * @author		WrathWings
 * @version 	V1.0
 * @date		2020.11.8
 * @brief		Header file of WPT_Tx.c
 ******************************************************************************
 * @attention
 *
 ******************************************************************************
 */
 
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __WPT_TX_H
#define __WPT_TX_H

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "hrtim.h"
#include "util.h"
/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define		HRCK_FREQ					(6.8 * (float)1e8)	//Hz
#define		TIMCK_FREQ					(170 * (float)1e6)	//Hz
#define		SAMPLING_FREQ				(200 * (float)1e3)	//Hz
#define		SWITCH_PERIOD_S				(1.f / WptTx.SwitchFreq)	//s
#define 	SWITCH_PERIOD_US			(SYSTEM_PERIOD_S * (float)1e6)	//us

#define		VOL_SAMPLING_RES_HS			100.0f	//KOhm
#define		VOL_SAMPLING_RES_LS			3.f		//KOhm
#define 	CURR_SAMPLING_RES			1e-3	//Ohm
#define		CURR_SAMPLING_AMP_GAIN		23.5f

#define		ADC_VREF					3.3f	//V
#define		ADC_RESOLUTION				4096.f	

/* USER CODE END PD */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
struct WptTx_t
{
	uint16_t ADC_Value[2];
	float 	 LoopVol;
	float 	 LoopCurr;
	float 	 SwitchFreq;
	float 	 LoopVolFactorSlope;		//线圈电压换算系数
	float 	 LoopVolFactorInterrupt;		//线圈电流换算截距
	float 	 LoopCurrFactorSlope;		//线圈电流换算系数
	float 	 LoopCurrFactorInterrupt;		//线圈电流换算截距
};

/* USER CODE END PTD */

/* Private prototypes --------------------------------------------------------*/
/* USER CODE BEGIN Prototypes */
void WPT_Tx_Init(void);
void WPT_Tx(void);
void ErrorAmplifier(void);
void GetVolCurr(void);
void VinAverageFilter(void);
void VoutAverageFilter(void);
void SetSwitchFreq(float exptFreq);
void ADConvert_Enable(void);
void HRTIM_PWM_Enable(void);
/* USER CODE END Prototypes */

#endif

/************************ (C) COPYRIGHT Action *****END OF FILE****/
