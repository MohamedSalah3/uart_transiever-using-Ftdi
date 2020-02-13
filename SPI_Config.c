/*
 * SPI_Config.c
 *
 * Created: 2020-02-10 10:31:20 PM
 *  Author: EbrahimOseif
 */ 
	#include "SPI_Config.h"
	
	struct ST_SPI_Configuration SPI_Config={
		SPI_MASTER,
		SPI_Fosc16,
		SPI_ENABLE_ON,
		SPI_DOUBLE_SPEED_MODE_OFF,
		SPI_IDLE_HIGH,
		SPI_LEADING ,
		//SPI_INT_OFF,
		SPI_LSB_FISRT
	};
