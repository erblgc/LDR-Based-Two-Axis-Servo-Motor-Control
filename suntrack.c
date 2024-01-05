#include <16F887.h>
#device adc = 10
#include <math.h>
#fuses NOWDT,XT,NOPUT,NOPROTECT,NODEBUG,NOBROWNOUT, NOLVP,NOCPD,NOWRT         
#use delay(clock=4M)

#define SERVO_DIKEY pin_d1
#define SERVO_YATAY pin_d0

void main()
{
   set_tris_d(0x00);
   set_tris_a(0xff);
   
   setup_adc_ports(sAN0|sAN1|sAN2|sAN3); // adc channels activating
   setup_adc(ADC_CLOCK_DIV_32);

   int unit = 20;
   int range = 10;
   int16 servo_dikey_s1 = 1000;
   int16 servo_dikey_s2 = 1000;
   int16 servo_yatay_s1 = 1000;
   int16 servo_yatay_s2 = 1000;
   
   int16 ldr_ust;
   int16 ldr_alt;
   int16 ldr_sag;
   int16 ldr_sol;

   int16 temp_dikey;
   int16 temp_yatay;

   while(true)
   {
      set_adc_channel(0);
      delay_us(20);
      ldr_ust = read_adc();
      
      set_adc_channel(1);
      delay_us(20);
      ldr_alt = read_adc();
      
      set_adc_channel(2);
      delay_us(20);
      ldr_sag = read_adc();
      
      set_adc_channel(3);
      delay_us(20);
      ldr_sol = read_adc();
           
      temp_dikey = fabs(ldr_ust - ldr_alt);
      temp_yatay = fabs(ldr_sag - ldr_sol);
        
      if (temp_dikey > range)
      {
         if(ldr_alt < (ldr_ust + range))
         {
            output_high(SERVO_DIKEY);
            delay_us(servo_dikey_s1);
            output_low(SERVO_DIKEY);
            delay_us(20000 - servo_dikey_s1);
            servo_dikey_s2 = servo_dikey_s1;
            if(servo_dikey_s1 <= 2000)
            {
               servo_dikey_s1 = servo_dikey_s1 + unit;
            }
         }
         else if(ldr_alt > (ldr_ust + range))
         {
            output_high(SERVO_DIKEY);
            delay_us(servo_dikey_s2);
            output_low(SERVO_DIKEY);
            delay_us(20000 - servo_dikey_s2);
            servo_dikey_s1 = servo_dikey_s2;
            if(servo_dikey_s2 >= 100)
            {
               servo_dikey_s2 = servo_dikey_s2 - unit;
            }
         }
      }
      else
      {
         output_low(SERVO_DIKEY);
      }
      if (temp_yatay > range)
      {
         if (ldr_sag < (ldr_sol + range))
         {
            output_high(SERVO_YATAY);
            delay_us(servo_yatay_s1);
            output_low(SERVO_YATAY);
            delay_us(20000 - servo_yatay_s1);
            servo_yatay_s2 = servo_yatay_s1;
            if(servo_yatay_s1 <= 2000)
            {
               servo_yatay_s1 = servo_yatay_s1 + unit;
               
            }
         }
         else if(ldr_sag > (ldr_sol + range))
         {
            output_high(SERVO_YATAY);
            delay_us(servo_yatay_s2);
            output_low(SERVO_YATAY);
            delay_us(20000 - servo_yatay_s2);
            servo_yatay_s1 = servo_yatay_s2;
            if(servo_yatay_s2 >= 100)
            {
               servo_yatay_s2 = servo_yatay_s2 - unit;
            }
         }
         else
         {
            output_low(SERVO_YATAY);
         }
      }             
   }
}
