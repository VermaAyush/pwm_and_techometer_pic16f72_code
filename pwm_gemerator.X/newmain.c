/*
 * File:   newmain.c
 * Author: electroGoal
 *
 * Created on 24 March, 2024, 7:54 PM
 */
// CONFIG
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config CP = OFF         // FLASH Program Memory Code Protection bit (Code protection off)
#pragma config BOREN = OFF       // Brown-out Reset Enable bit (BOR enabled)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#define _XTAL_FREQ 16000000
#include <xc.h>
#define SEG_A   PORTBbits.RB0
#define SEG_B   PORTBbits.RB1
#define SEG_C   PORTBbits.RB2
#define SEG_D   PORTBbits.RB3
#define SEG_E   PORTBbits.RB4
#define SEG_F   PORTBbits.RB5
#define SEG_G   PORTBbits.RB6
#define SEG_DP  PORTBbits.RB7

void displayDigit(int digit) {
    // Define the common cathode pins to turn on
    switch (digit) {
         case 0:
            SEG_A = 0;
            SEG_B = 0;
            SEG_C = 0;
            SEG_D = 0;
            SEG_E = 0;
            SEG_F = 0;
            SEG_G = 1;
            break;
        case 1:
            SEG_A = 1;
            SEG_B = 0;
            SEG_C = 0;
            SEG_D = 1;
            SEG_E = 1;
            SEG_F = 1;
            SEG_G = 1;
            break;
        case 2:
            SEG_A = 0;
            SEG_B = 0;
            SEG_C = 1;
            SEG_D = 0;
            SEG_E = 0;
            SEG_F = 1;
            SEG_G = 0;
            break;
        case 3:
            SEG_A = 0;
            SEG_B = 0;
            SEG_C = 0;
            SEG_D = 0;
            SEG_E = 1;
            SEG_F = 1;
            SEG_G = 0;
            break;
        case 4:
            SEG_A = 1;
            SEG_B = 0;
            SEG_C = 0;
            SEG_D = 1;
            SEG_E = 1;
            SEG_F = 0;
            SEG_G = 0;
            break;
        case 5:
            SEG_A = 0;
            SEG_B = 1;
            SEG_C = 0;
            SEG_D = 0;
            SEG_E = 1;
            SEG_F = 0;
            SEG_G = 0;
            break;
        case 6:
            SEG_A = 0;
            SEG_B = 1;
            SEG_C = 0;
            SEG_D = 0;
            SEG_E = 0;
            SEG_F = 0;
            SEG_G = 0;
            break;
        case 7:
            SEG_A = 0;
            SEG_B = 0;
            SEG_C = 0;
            SEG_D = 1;
            SEG_E = 1;
            SEG_F = 1;
            SEG_G = 1;
            break;
        case 8:
            SEG_A = 0;
            SEG_B = 0;
            SEG_C = 0;
            SEG_D = 0;
            SEG_E = 0;
            SEG_F = 0;
            SEG_G = 0;
            break;
        case 9:
            SEG_A = 0;
            SEG_B = 0;
            SEG_C = 0;
            SEG_D = 0;
            SEG_E = 1;
            SEG_F = 0;
            SEG_G = 0;
            break;
        default:
            // Turn off all segments for invalid inputs or display blank
            SEG_A = 1;
            SEG_B = 1;
            SEG_C = 1;
            SEG_D = 1;
            SEG_E = 1;
            SEG_F = 1;
            SEG_G = 1;
            break;
    }
}
void main(void) {
     int duty_cycle =3;
     int speed[] = {1,25,50,75,100,125,150,175,200,225};
     int button_state = 0;
     int button_push_counter = 0;
     int last_button_state = 0;
      int button2_state = 0;
     int button2_push_counter = 0;
     int last_button2_state = 0;
     
    unsigned char fade_direction = 1;  // 1 for fade in, 0 for fade out
    
    // Set up CCP1 module for PWM operation
    CCP1CON = 0b00001100;   // Configure CCP1 module for PWM mode
    TRISCbits.TRISC2 = 0;   // Make CCP1 pin (RC2) as output
    
    // Set up Timer2 for PWM frequency
    T2CON = 0b00000111;     // Timer2 on, prescaler 1:16
    PR2 = 0xff;             // Set PWM period
    TRISC4 = 1;             // set RC4 at input for pwm setting  up    
    TRISC5 = 1;             // set RC4 at input for pwm setting  down
    // Main loop 
   // CCPR1L = speed[5];
     TRISB = 0x00;  // Set PORTB as output
    //PORTB = 0x00;  // Initialize PORTB to 0
      // Turn on LEDs one by one
     for(int i = 0;i<3;i++){    PORTB = ~ 1;
     __delay_ms(50);
     PORTB = ~ 2;
     __delay_ms(50);
     PORTB = ~ 4;
     __delay_ms(50);
     PORTB = ~ 8;
     __delay_ms(50);
     PORTB = ~ 16;
     __delay_ms(50);
     PORTB = ~ 32;
     __delay_ms(50);
     PORTB = ~ 64;
}
     
     
    while(1) {
        button_state = RC5;
        button2_state = RC4;
        if(button_state != last_button_state){
            if(button_state == 0){
                duty_cycle = duty_cycle + 1;
               if(duty_cycle >=9){
                    duty_cycle = 9;
                }
                if(duty_cycle <= 0){
                    duty_cycle = 0;
                }
            CCPR1L = speed[duty_cycle];
                
            }else{
                
            }
            __delay_ms(50);
        }
            // Update duty cycle
        
        if(button2_state != last_button2_state){
            if(button2_state == 0){
                duty_cycle = duty_cycle - 1;
                if(duty_cycle >= 9){
                    duty_cycle = 9;
                }
                if(duty_cycle <= 0){
                    duty_cycle = 0;
                }
            CCPR1L = speed[duty_cycle];
                
            }else{
                
            }
            __delay_ms(50);
        } 
        last_button_state = button_state;   
        last_button2_state = button2_state;
      displayDigit(duty_cycle);
    }

}
