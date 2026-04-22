#ifndef INCFILE1_H_
#define INCFILE1_H_
#define MOTOR_PORT   PORTD
#define MOTOR_DDR    DDRD
#define MOTOR_IN1    0  // IN1 L293D
#define MOTOR_IN2    1  // IN2 L293D
#define MOTOR_EN     6   // Enable Pin
void MOTOR_Init(void);
void MOTOR_Forward(void);
void MOTOR_Backward(void);
void MOTOR_Stop(void);
#endif /* INCFILE1_H_ */
