/*
 * MUART_program.c
 *
 *  Created on: Jan 24, 2024
 *      Author: BROTHERS
 */

/***************	MUSART1 Files include	***************/
/*Standard LIBS*/
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
/*MUSART1 files*/
#include "MUART1_config.h"
#include "MUART1_interface.h"
#include "MUART1_private.h"
#include "MUART1_register.h"
/*********************************************/
/*********************************************/

/***************	Global variables	***************/
void (*Gpv_MUSART1_CallBACK_Func)(void)= NULL;
/*********************************************/
/*********************************************/

/***************	MUSART1 Functions Implementations	***************/
/********************************************************************************************/
/* @Name  	  :->		@ MUSART1_voidInit												 	*/
/* @Brief 	  :->		@ used to initialize USART 1 Configurations							 	*/
/* @parameters   :-> 	@ void																*/
/* @PreRequsteis :->	@ the Peripheral clock must be enabled in the RCC 					*/
/********************************************************************************************/
void MUSART1_voidInit(void){
	/*set baud rate 9600*/
		MUSART1->BRR = MUSART1_BAUD_RATE;
	/*set stop bit*/
		CLR_BIT(MUSART1->CR2,12);
		CLR_BIT(MUSART1->CR2,13);
	/*word length*/
		CLR_BIT(MUSART1->CR1,12);
	/*set sampling*/
		CLR_BIT(MUSART1->CR1,15);
		/*one Sample Bit*/
		SET_BIT(MUSART1->CR3,11);
	/*enable transmit*/
		SET_BIT(MUSART1->CR1,3);
	/*enable receive*/
		SET_BIT(MUSART1->CR1,2);
}

/********************************************************************************************/
/* @Name  	  :->		@ MUSART1_voidSendData											 	*/
/* @Brief 	  :->		@ used to send data using USART 1								 	*/
/* @parameters   :-> 	@ Copy_u8Data-> data to be sent										*/
/* @PreRequsteis :->	@ the Peripheral clock must be enabled in the RCC 					*/
/*						@ USART1 must be initialized										*/
/********************************************************************************************/
void MUSART1_voidSendData(u8 Copy_u8Data){
	MUSART1->DR=Copy_u8Data;
	while(GET_BIT(MUSART1->SR,7)==0){
			asm("NOP");
		}
}

/********************************************************************************************/
/* @Name  	  :->		@ MUSART1_voidReciveData											 	*/
/* @Brief 	  :->		@ used to receive data using USART 1							 	*/
/*						@ returns a u8 data from the receiving process						*/
/* @parameters   :-> 	@ void																*/
/* @PreRequsteis :->	@ the Peripheral clock must be enabled in the RCC 					*/
/*						@ USART1 must be initialized										*/
/********************************************************************************************/
u8 MUSART1_voidReciveData(void){
	while((GET_BIT(MUSART1->SR,5))!=1){
			asm("NOP");
	}
	return (u8) MUSART1->DR;
}

/********************************************************************************************/
/* @Name  	  :->		@ MUSART1_voidRecieveAsynchronous								 	*/
/* @Brief 	  :->		@ used to receive data using USART 1 interrupt					 	*/
/*						@ returns a u8 data from the receiving process						*/
/* @parameters   :-> 	@ void																*/
/* @PreRequsteis :->	@ the Peripheral clock must be enabled in the RCC 					*/
/*						@ USART1 must be initialized										*/
/*						@ USART1 interrupt must be enabled using NVIC						*/
/********************************************************************************************/
u8 MUSART1_voidRecieveAsynchronous(void){
	return (u8) MUSART1->DR;
}

/********************************************************************************************/
/* @Name  	  :->		@ MUSART1_voidEnableInterrupt								 	*/
/* @Brief 	  :->		@ used to enable USART1 interrupt					 				*/
/* @parameters   :-> 	@ void																*/
/* @PreRequsteis :->	@ the Peripheral clock must be enabled in the RCC 					*/
/*						@ USART1 must be initialized										*/
/*						@ USART1 interrupt must be enabled using NVIC						*/
/********************************************************************************************/
void MUSART1_voidEnableInterrupt(void)
{
	SET_BIT(MUSART1->CR1,5);
}

/********************************************************************************************/
/* @Name  	  :->		@ MUSART1_voidDisbleInterrupt								 		*/
/* @Brief 	  :->		@ used to disable USART1 interrupt					 				*/
/* @parameters   :-> 	@ void																*/
/* @PreRequsteis :->	@ the Peripheral clock must be enabled in the RCC 					*/
/*						@ USART1 must be initialized										*/
/********************************************************************************************/
void MUSART1_voidDisbleInterrupt(void)
{
	SET_BIT(MUSART1->CR1,5);
}

/********************************************************************************************/
/* @Name  	  :->		@ MUSART1_voidEnable												 	*/
/* @Brief 	  :->		@ used to Enable USART 1 registers	 							 	*/
/* @parameters   :-> 	@ void																*/
/* @PreRequsteis :->	@ the Peripheral clock must be enabled in the RCC 					*/
/********************************************************************************************/
void MUSART1_voidEnable(void){
	SET_BIT(MUSART1->CR1,13);
}

/********************************************************************************************/
/* @Name  	  :->		@ MUSART1_voidDisable											 	*/
/* @Brief 	  :->		@ used to Disable USART 1 registers	 							 	*/
/* @parameters   :-> 	@ void																*/
/* @PreRequsteis :->	@ the Peripheral clock must be enabled in the RCC 					*/
/********************************************************************************************/
void MUSART1_voidDisable(void){
	CLR_BIT(MUSART1->CR1,13);
}

/********************************************************************************************/
/* @Name  	  :->		@ MUSART1_voidSendString											 	*/
/* @Brief 	  :->		@ used to send String data using USART 1							*/
/* @parameters   :-> 	@ Copy_pu8Ddata-> Pointer to string data to be sent					*/
/* @PreRequsteis :->	@ the Peripheral clock must be enabled in the RCC 					*/
/*						@ USART1 must be initialized										*/
/********************************************************************************************/
void MUSART1_voidSendString(u8 *Copy_pu8Data){
	u8 L_u8Iterator=0;
	while ( Copy_pu8Data[L_u8Iterator] != '\0')
		{
			MUSART1->DR = Copy_pu8Data[L_u8Iterator];
			while( GET_BIT(MUSART1->SR,7) == 0 );
			L_u8Iterator++;
		}
}

/********************************************************************************************/
/* @Name  	  :->		@ MUSART1_voidSetCallBack										 	*/
/* @Brief 	  :->		@ used to send String data using USART 1							*/
/* @parameters   :-> 	@ vp_Fumc-> Pointer to ISR CALLBACK func							*/
/* @PreRequsteis :->	@ the Peripheral clock must be enabled in the RCC 					*/
/*						@ USART1 must be initialized										*/
/********************************************************************************************/
void MUSART1_voidSetCallBack(void(*vp_Func)(void)){
	Gpv_MUSART1_CallBACK_Func=vp_Func;
}

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/****	USART1 interrupt handler ****/
void USART1_IRQHandler(void){
	//MUSART1 -> SR = 0;
	if(Gpv_MUSART1_CallBACK_Func!=NULL){
		Gpv_MUSART1_CallBACK_Func();
	}



}
