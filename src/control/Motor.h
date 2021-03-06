/*
 * PIDControl.h
 *
 *  Created on: Mar 12, 2016
 *      Author: lenovoi7
 */

#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "GPIO.h"
#include "Pwm.h"
#include "Encoder.h"
//#include "TimerTime2.h"
//#include "hal/ina220.h"

#ifndef MOTOR_H_
#define MOTOR_H_

//valor aproximado do raio da roda omni, em metros
#define R_roda 0.028
#define PI 3.1415926
//tempo (em s) entre as interrup��es geradas pelo TIM6
#define TIM6_delay 0.001
//n�mero de divis�es do encoder
#define ENC_DIV 400
//para cada 8 giros do motor, a roda gira 1 vez
#define FT_TRANS 8
#define CONVERSION 2*PI*R_roda/(TIM6_delay*ENC_DIV*FT_TRANS)

class Motor {
public:
	Motor(  Pwm *A_High,
			GPIO *A_Low,
			Pwm *B_High,
			GPIO *B_Low,
			Encoder *Enc);
			//Timer_Time2 *MTimer


	//void Control_Pos(float hold_position);
	float Get_control_signal();

	void Control_Speed(float desired_speed);
	void Get_Speed();
	void Set_Speed(float speed);

	int16_t Get_Desloc();//retorna o deslocamento do eixo do motor, unidade: divis�es de encoder

	static void SetPID(float p, float i, float d);
	static void GetPID(float p, float i, float d);

	float real_wheel_speed;
private:
	Pwm *Motor_A_High;
	Pwm *Motor_B_High;
	GPIO *Motor_A_Low;
	GPIO *Motor_B_Low;
	Encoder *Motor_Enc;
	//Timer_Time2 *Motor_Time;

	int16_t last_position;
	int16_t dutycycle;

	int16_t current_position;
	int16_t enc_position[10];

	float control_signal; //valor de dutycycle calculado pela malha de controle
	float lasterror;
	float error;
	float derror;
	float last_error[20];
	float ierror;
	static float cp;
	static float cd;
	static float ci;


};
#endif /* MOTOR_H_ */
