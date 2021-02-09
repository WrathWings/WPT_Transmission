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
	WptTx.SwitchFreq = 25 * 1e3;
	WptTx.CapDuty = 0.5;
	
	SetSwitchFreq(WptTx.SwitchFreq);
	SetCapDuty(WptTx.CapDuty);
	
	/*计算系数, 以减少每周期运算量*/
	WptTx.LoopVolFactorSlope = ADC_VREF /ADC_RESOLUTION * ((VOL_SAMPLING_RES_HS + VOL_SAMPLING_RES_LS) / VOL_SAMPLING_RES_LS);
	WptTx.LoopVolFactorInterrupt = - (ADC_VREF / 2.f) * ((VOL_SAMPLING_RES_HS + VOL_SAMPLING_RES_LS) / VOL_SAMPLING_RES_LS);
	WptTx.LoopCurrFactorSlope = ADC_VREF / ADC_RESOLUTION / CURR_SAMPLING_AMP_GAIN / CURR_SAMPLING_RES;
	WptTx.LoopCurrFactorInterrupt = - ADC_VREF / CURR_SAMPLING_AMP_GAIN / CURR_SAMPLING_RES / 2.f;
	
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
	WptTx.LoopVol = WptTx.LoopVolFactorSlope*WptTx.ADC_Value[0] + WptTx.LoopVolFactorInterrupt;
	WptTx.LoopCurr = WptTx.LoopCurrFactorSlope*WptTx.ADC_Value[1] + WptTx.LoopCurrFactorInterrupt;
}

void SetSwitchFreq(float exptFreq)
{
	uint16_t exptPeriod = 0;		
	uint16_t exptCCR = 0;
	
	exptPeriod = HRCK_FREQ/exptFreq;
	Saturation_uint16(&exptPeriod, 65527, 24);
	exptCCR = exptPeriod/2;
	
	/*设定逆变器开关频率*/
	__HAL_HRTIM_SETPERIOD(&hhrtim1, HRTIM_TIMERINDEX_TIMER_C, (uint16_t)exptPeriod);
	__HAL_HRTIM_SETCOMPARE(&hhrtim1, HRTIM_TIMERINDEX_TIMER_C, HRTIM_COMPAREUNIT_1, exptCCR);
	
	/*设定可控电容开关频率*/
	__HAL_HRTIM_SETPERIOD(&hhrtim1, HRTIM_TIMERINDEX_TIMER_D, (uint16_t)exptPeriod);
}

void SetCapDuty(float duty)
{
	uint16_t presentPeriod = 0;
	uint16_t exptCCR = 0;
	
	/*获取当前周期*/
	presentPeriod = __HAL_HRTIM_GETPERIOD(&hhrtim1, HRTIM_TIMERINDEX_TIMER_D);
	
	Saturation_float(&duty, 1.f, 0.f);
	
	/*设定CCR值*/
	exptCCR = (uint16_t)(duty*presentPeriod);
	__HAL_HRTIM_SETCOMPARE(&hhrtim1, HRTIM_TIMERINDEX_TIMER_D, HRTIM_COMPAREUNIT_1, exptCCR);
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
	
	__HAL_HRTIM_ENABLE(&hhrtim1, HRTIM_TIMERID_TIMER_D);
	HAL_HRTIM_WaveformOutputStart(&hhrtim1, HRTIM_OUTPUT_TD1);

	HAL_HRTIM_WaveformCountStart(&hhrtim1, HRTIM_TIMERID_TIMER_C | HRTIM_TIMERID_TIMER_D);	//同时启动TimerC和TimerD的计时器, 以尽可能使二者同步
}

/* USER CODE END */

/************************ (C) COPYRIGHT Action *****END OF FILE****/
