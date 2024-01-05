#include <16F887.h>
#device adc = 10
#include <math.h>
#fuses NOWDT,XT,NOPUT,NOPROTECT,NODEBUG,NOBROWNOUT, NOLVP,NOCPD,NOWRT         
#use delay(clock=4M)

#define SERVO_VERTICAL pin_d1
#define SERVO_HORIZANTAL pin_d0

void main()
{
   set_tris_d(0x00);
   set_tris_a(0xff);
   
   setup_adc_ports(sAN0|sAN1|sAN2|sAN3); // adc channels activating
   setup_adc(ADC_CLOCK_DIV_32);

   int unit = 20;
   int range = 10;
   int16 servo_vert_s1 = 1000;
   int16 servo_vert_s2 = 1000;
   int16 servo_hor_s1 = 1000;
   int16 servo_hor_s2 = 1000;
   
   int16 ldr_top;
   int16 ldr_bot;
   int16 ldr_right;
   int16 ldr_left;

   int16 temp_hor;
   int16 temp_vert;

   while(true)
   {
      set_adc_channel(0);
      delay_us(20);
      ldr_top = read_adc();
      
      set_adc_channel(1);
      delay_us(20);
      ldr_bot = read_adc();
      
      set_adc_channel(2);
      delay_us(20);
      ldr_right = read_adc();
      
      set_adc_channel(3);
      delay_us(20);
      ldr_left = read_adc();
           
      temp_vert = fabs(ldr_top - ldr_bot);
      temp_hor = fabs(ldr_right - ldr_left);
        
      if (temp_vert > range)
      {
         if(ldr_bot < (ldr_top + range))
         {
            output_high(SERVO_VERTICAL);
            delay_us(servo_vert_s1);
            output_low(SERVO_VERTICAL);
            delay_us(20000 - servo_vert_s1);
            servo_vert_s2 = servo_vert_s1;
            if(servo_vert_s1 <= 2000)
            {
               servo_vert_s1 = servo_vert_s1 + unit;
            }
         }
         else if(ldr_bot > (ldr_top + range))
         {
            output_high(SERVO_VERTICAL);
            delay_us(servo_vert_s2);
            output_low(SERVO_VERTICAL);
            delay_us(20000 - servo_vert_s2);
            servo_vert_s1 = servo_vert_s2;
            if(servo_vert_s2 >= 100)
            {
               servo_vert_s2 = servo_vert_s2 - unit;
            }
         }
      }
      else
      {
         output_low(SERVO_VERTICAL);
      }
      if (temp_hor > range)
      {
         if (ldr_right < (ldr_left + range))
         {
            output_high(SERVO_HORIZANTAL);
            delay_us(servo_hor_s1);
            output_low(SERVO_HORIZANTAL);
            delay_us(20000 - servo_hor_s1);
            servo_hor_s2 = servo_hor_s1;
            if(servo_hor_s1 <= 2000)
            {
               servo_hor_s1 = servo_hor_s1 + unit;
               
            }
         }
         else if(ldr_right > (ldr_left + range))
         {
            output_high(SERVO_HORIZANTAL);
            delay_us(servo_hor_s2);
            output_low(SERVO_HORIZANTAL);
            delay_us(20000 - servo_hor_s2);
            servo_hor_s1 = servo_hor_s2;
            if(servo_hor_s2 >= 100)
            {
               servo_hor_s2 = servo_hor_s2 - unit;
            }
         }
         else
         {
            output_low(SERVO_HORIZANTAL);
         }
      }             
   }
}













