/*
 * Timer1.c
 *
 *  Created on:Febr 9, 2021
 *      Author: SAID_MAGDY
 */
#include "../../LIBRARIES/stdTypes.h"
#include "../../LIBRARIES/errorStates.h"
#include "../../LIBRARIES/bit_math.h"
#include "../../LIBRARIES/AVR_REG.h"
#include  "Timer1_Config.h"
#include  "Timer1_int.h"
//#define F_CPU 8000000ul
ES_t Timer1_init() {
#if TIMER1_MODE == TIMER1_NORMAL
	CLR_BIT(TCCR1A, WGM10);
	CLR_BIT(TCCR1A, WGM11);
	CLR_BIT(TCCR1A, WGM12);
#elif TIMER1_MODE == TIMER1_PWM_PHASE_CORRECT_8
	SET_BIT(TCCR1A, WGM10);
	CLR_BIT(TCCR1A, WGM11);
	CLR_BIT(TCCR1A, WGM12);
#elif TIMER1_MODE == TIMER1_PWM_PHASE_CORRECT_9
	CLR_BIT(TCCR1A, WGM10);
	SET_BIT(TCCR1A, WGM11);
	CLR_BIT(TCCR1A, WGM12);
#elif TIMER1_MODE == TIMER1_PWM_PHASE_CORRECT_10
	SET_BIT(TCCR1A, WGM10);
	SET_BIT(TCCR1A, WGM11);
	CLR_BIT(TCCR1A, WGM12);
#elif TIMER1_MODE == TIMER1_CTC
	CLR_BIT(TCCR1A, WGM10);
	CLR_BIT(TCCR1A, WGM11);
	SET_BIT(TCCR1A, WGM12);
#elif TIMER1_MODE == TIMER1_PWM_FAST_8
	SET_BIT(TCCR1A, WGM10);
	CLR_BIT(TCCR1A, WGM11);
	SET_BIT(TCCR1A, WGM12);
#elif TIMER1_MODE == TIMER1_PWM_FAST_9
	CLR_BIT(TCCR1A, WGM10);
	SET_BIT(TCCR1A, WGM11);
	SET_BIT(TCCR1B, WGM12);
	SET_BIT(TCCR1B, WGM13);
#elif TIMER1_MODE == TIMER1_PWM_FAST_10
	SET_BIT(TCCR1A, WGM10);
	SET_BIT(TCCR1A, WGM11);
	SET_BIT(TCCR1B, WGM12);
	SET_BIT(TCCR1B, WGM13);
#endif

#if TIMER1_COMPARE_OUTPUT == COM_OUT_DIS
	CLR_BIT(TCCR1A, COM1A0);
	CLR_BIT(TCCR1A, COM1A1);
#elif TIMER1_COMPARE_OUTPUT == COM_OUT_TOG
	SET_BIT(TCCR1A,COM1A0);
	CLR_BIT(TCCR1A,COM1A1);
#elif TIMER1_COMPARE_OUTPUT == COM_OUT_CLR
	CLR_BIT(TCCR1A,COM1B0);
	SET_BIT(TCCR1A,COM1B1);
	SET_BIT(TCCR1A,COM1A1);
#elif TIMER1_COMPARE_OUTPUT == COM_OUT_SET
	SET_BIT(TCCR1A,COM1A0);
	SET_BIT(TCCR1A,COM1A1);
#endif

#if TIMO_PRES == TIMO_NO_CLK
	CLR_BIT(TCCR1B, CS10);
	CLR_BIT(TCCR1B, CS11);
	CLR_BIT(TCCR1B, CS12);
#elif TIMO_PRES == TIMO_NO_PRES
	SET_BIT(TCCR1B, 0);
	CLR_BIT(TCCR1B, 1);
	CLR_BIT(TCCR1B, 2);
#elif TIMO_PRES == TIMO_8_PRES
	CLR_BIT(TCCR1B, 0);
	SET_BIT(TCCR1B, 1);
	CLR_BIT(TCCR1B, 2);
#elif TIMO_PRES == TIMO_64_PRES
	SET_BIT(TCCR1B, CS10);
	SET_BIT(TCCR1B, CS11);
	CLR_BIT(TCCR1B, CS12);
#elif TIMO_PRES == TIMO_256_PRES
	CLR_BIT(TCCR1B, 0);
	CLR_BIT(TCCR1B, 1);
	SET_BIT(TCCR1B, 2);
#elif TIMO_PRES == TIMO_1024_PRES
	SET_BIT(TCCR1B, 0);
	CLR_BIT(TCCR1B, 1);
	SET_BIT(TCCR1B, 2);
#endif
	/*TIMSK |=(1<<2);
	TIMSK |=(1<<3);
	TIMSK |=(1<<4);*/
	return ES_OK ;
	}
ES_t Timer_PWM(float Copy_u16Freq ,float Copy_u8DutyCycle){
	ES_t Local_enuErrorState =ES_NOK;
	if(Copy_u8DutyCycle < 100 && Copy_u8DutyCycle > 0){
		float volatile Local_u8Itrator ;
		float volatile Local_u8Itrator2 ;
		ICR1 = (16000000.0/(Copy_u16Freq * 64.0))-1 ;
		Local_u8Itrator = (u16)((Copy_u8DutyCycle * ICR1)/100.0);
		//Local_u8Itrator2 = (u16)((Copy_u8DutyCycle * ICR1)/100.0);


		//ICR1 = Local_u8Itrator;
		/*ICR1H =(4999 & 0xff00);
		ICR1L =(4999 & 0x00ff);*/



		OCR1A =Local_u8Itrator ;
		OCR1B = Local_u8Itrator;

        Local_enuErrorState =ES_OK;
	}
	return Local_enuErrorState ;
}
