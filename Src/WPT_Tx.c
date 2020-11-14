/**
 ******************************************************************************
 * @file		WPT_Tx.c
 * @author		WrathWings
 * @version 	V1.0
 * @date		2020.11.8
 * @brief		Functions to control the WPT transmission part
 ******************************************************************************
 * @attention
 *
 ******************************************************************************
 */
 
/* Includes ------------------------------------------------------------------*/
#include "WPT_Tx.h"

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

struct WptTx_t WptTx;
	
/* USER CODE END PV */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN */

void WPT_Tx_Init(void)
{
	WptTx.SwitchFreq = 27 * 1e3;
	
	SetSwitchFreq(WptTx.SwitchFreq);
	
	/*计算系数, 以减少每周期运算量*/
	WptTx.LoopVolFactorSlope = ADC_VREF /ADC_RESOLUTION * ((VOL_SAMPLING_RES_HS + VOL_SAMPLING_RES_LS) / VOL_SAMPLING_RES_LS);
	WptTx.LoopCurrFactorSlope = ADC_VREF / ADC_RESOLUTION / CURR_SAMPLING_AMP_GAIN / CURR_SAMPLING_RES;
	
	ADConvert_Enable();
	HRTIM_PWM_Enable();
}

void WPT_Tx(void)
{
	/*计算输入输出电压*/
	GetVolCurr();
		
} 

void GetVolCurr(void)
{
	WptTx.LoopVol = WptTx.LoopVolFactorSlope * WptTx.ADC_Value[0];
	WptTx.LoopCurr = WptTx.LoopCurrFactorSlope * WptTx.ADC_Value[1];
}

void SetSwitchFreq(float exptFreq)
{
	__HAL_HRTIM_SETPERIOD(&hhrtim1, HRTIM_TIMERINDEX_TIMER_C, (uint16_t)(HRCK_FREQ/exptFreq));
	__HAL_HRTIM_SETCOMPARE(&hhrtim1, HRTIM_TIMERINDEX_TIMER_C, HRTIM_COMPAREUNIT_1, (uint16_t)(HRCK_FREQ/exptFreq/2.f));
}

void ADConvert_Enable(void)
{
	HAL_ADC_Stop(&hadc5);
	
	HAL_ADC_Start_DMA(&hadc5, (uint32_t *)WptTx.ADC_Value, 2u);
	
	/*关闭DMA中断*/
	__HAL_DMA_DISABLE_IT(hadc5.DMA_Handle, DMA_IT_TC|DMA_IT_HT);
}

void HRTIM_PWM_Enable(void)
{
	__HAL_HRTIM_ENABLE(&hhrtim1, HRTIM_TIMERID_TIMER_C);
	HAL_HRTIM_WaveformOutputStart(&hhrtim1, HRTIM_OUTPUT_TC1 | HRTIM_OUTPUT_TC2);
	HAL_HRTIM_WaveformCounterStart(&hhrtim1, HRTIM_TIMERID_TIMER_C);
}

/* USER CODE END */

/************************ (C) COPYRIGHT Action *****END OF FILE****/
