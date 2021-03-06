#pragma once
#ifndef DATA_FORMAT_H
#define DATA_FORMAT_H

#define IP_ADDRESS "192.168.0.26"

#include <string>
#include <string.h>


using namespace std;
/*		   ID	     */
#define CPP			0
#define REI			1
#define STT			2
/* TOUCH SENSOR MODE */
#define DEFAULT		0
#define HEAD		1
#define BODY		2
#define FIN			3
#define TAIL		4
/*	  SENSOR MODE  	 */	
#define OFF			0
#define ON			1
/*	   OLED MODE	 */
#define NORM		0
#define HAPPY		1
#define SAD			2
#define ANGRY		3
#define BORED		4
#define FUN			5
/*		FIN MODE	 */
#define SHAKE		0
#define WING		1
#define DOWN		2
#define SLOW		3
#define NOMOVE		4
/*	   TAIL MODE	 */
#define FAST		0
#define SLOW		1
//#define DOWN		2
#define UP			3
//#define NOMOVE	4
/*FACE DETECT & MOTIONFLAG*/
#define NO			0
#define YES			1


string Data_Packet[9][6] = {
	{"cpp","rei","stt"},					// ID
	{"000"},								// ����� Parameter
	{"000"},								// �ǰ��� Parameter
	{"T0","T1","T2","T3","T4"},		// Touch Sensor 0: Default 1: Head 2: Body 3: Fin 4: Tail
	{"F0","F1"},							// Force Sensor 0: OFF 1: ON
	{"L0","L1"},							// Lift Sensor 0: OFF 1: ON
	{"O0","O1","O2","O3","O4","O5"},	// OLED (0~5) 
	{"F0","F1","F2","F3","F4"},		// FIN (0~3)
	{"t0","t1","t2","t3","t4"},		// TAIL (0~3)
};

string Mode[20] = {
	"002",//NORM		SHAKE		DOWN	0
	"020",//NORM		DOWN		FAST	1
	"030",//NORM		SLOW		FAST	2
	"011",//NORM		WING		SLOW	3
	"100",//HAPPY		SHAKE		FAST	4
	"101",//HAPPY		SHAKE		SLOW	5
	"131",//HAPPY		SLOW		SLOW	6
	"212",//SAD			WING		DOWN	7
	"221",//SAD			DOWN		SLOW	8
	"222",//SAD			DOWN		DOWN	9
	"232",//SAD			SLOW		DOWN	10
	"300",//ANGRY		SHAKE		FAST	11
	"303",//ANGRY		SHAKE		UP		12
	"313",//ANGRY		WING		UP		13
	"323",//ANGRY		DOWN		UP		14
	"421",//BORED		DOWN		SLOW	15
	"422",//BORED		WING		DOWN	16
	"431",//BORED		SLOW		SLOW	17
	"510",//FUN			WING		FAST	18
	"513",//FUN			WING		UP		19
};

/* Packet Global Variables */
volatile int				  Id = CPP;
volatile int		 Hungry_Para = 100;
volatile int		  Tired_Para = 100;
volatile int Touch_Sensor = DEFAULT;
volatile int		Force_Sensor = OFF;
volatile int		 Lift_Sensor = OFF;
volatile int		 Oled_State = NORM;
volatile int		Fin_State = NOMOVE;
volatile int	   Tail_State = NOMOVE;
volatile int		  Face_Detect = NO;
volatile int				Reward = 0;
volatile int		   Mode_Select = 0;
volatile int			  Stt_Data = 0;
volatile int					windo_change = OFF;

/* Global Variables */

void Send_Init_Variable() {
	Touch_Sensor = DEFAULT;
	Force_Sensor	 = OFF;
	Lift_Sensor		 = OFF;
	Reward			   = 0;
}
void Recv_Init_Variable() {
	Stt_Data		   = 0;
	Face_Detect		  = NO;
}

#endif