#include <mega8.h>
#include <delay.h>
#include <alcd.h>
#include <stdio.h>
#include <stdlib.h>

long duty = 50;
int waitMicroSeconds = 5000;
int pulseCount = 50;
char rotation = 'R';
int val = 50;
char temp[5] = "50";

void setSpeed(int wms , int pc);
void doStep(int st);
void motorOff(void);
void fullStep(int cnt,char forwards);
void halfStep(int cnt,char forwards);
void u16Step(int cnt, char forwards);
void u24Step(int cnt, char forwards);
void u32Step(int cnt, char forwards);
void u48Step(int cnt, char forwards);
void u64Step(int cnt, char forwards);
void u96Step(int cnt, char forwards);

interrupt [EXT_INT0] void ext_int0_isr(void)
{
 motorOff();
 val += 5;
 itoa(val, temp);
 lcd_gotoxy(0, 2);
 lcd_puts("Speed PC: ");
 lcd_puts(temp);
}

interrupt [EXT_INT1] void ext_int1_isr(void)
{
 motorOff();
 val -= 5;
 itoa(val, temp);
 lcd_gotoxy(0, 2);
 lcd_puts("Speed PC: ");
 lcd_puts(temp);
}

void main(void)
{
PORTB=0x00;
DDRB=0x00;

PORTC=0x00;
DDRC=0x0F;

PORTD=0x00;
PORTD=0x00;

GICR|=0xC0;
MCUCR=0x0F;
GIFR=0xC0;

#asm("sei")

lcd_init(16);

while (1)
      {
      setSpeed(5000, val);
      lcd_clear();
      lcd_gotoxy(0, 0);
      lcd_puts(" Stepper-Motor");
      
      if (PIND.0 == 0x01)
      {
       switch (rotation)
       {
        case 'R':
            rotation = 'L';break;
        case 'L':
            rotation = 'R';break;
       }
      }
      lcd_gotoxy(0, 1);
      lcd_puts("Rotation: ");
      switch (rotation)
       {
        case 'R':
            lcd_puts("Right");break;
        case 'L':
            lcd_puts("Left");break;
       }
      lcd_gotoxy(0, 2);
      lcd_puts("Speed PC: ");
      lcd_puts(temp);
              
//      fullStep(1,rotation);
//      halfStep(1,rotation);
      u16Step(1,rotation);
//      u24Step(1,rotation);
//      u32Step(1,rotation);
//      u48Step(1,rotation);
//      u64Step(1,rotation);
//      u96Step(1,rotation);
//      motorOff(); 
//      delay_ms(6);
      }
}

void setSpeed(int wms , int pc){
    waitMicroSeconds = wms;
    pulseCount = pc;
}

void doStep(int st){
  int k=0;
  long dt1 = (waitMicroSeconds * duty / 100)/1000;
  long dt2 = (waitMicroSeconds * (100-duty) / 100)/1000;
 
  for (k = 0; k < pulseCount; k++){
    switch (st){
    case 1: PORTC=0x05;break;
    case 2: PORTC=0x09;break;
    case 3: PORTC=0x0A;break;
    case 4: PORTC=0x06;break;
    case 11: PORTC=0x01;break;
    case 12: PORTC=0x08;break;
    case 13: PORTC=0x02;break;
    case 14: PORTC=0x04;break;

    case 21: PORTC=0x05;break;
    case 22: PORTC=0x09;break;
    case 23: PORTC=0x0A;break;
    case 24: PORTC=0x06;break;
    case 31: PORTC=0x01;break;
    case 32: PORTC=0x08;break;
    case 33: PORTC=0x02;break;
    case 34: PORTC=0x04;break;;
    }

    delay_ms(dt1);
    switch (st){
    case 1: PORTC=0x05;break;
    case 2: PORTC=0x09;break;
    case 3: PORTC=0x0A;break;
    case 4: PORTC=0x06;break;
    case 11: PORTC=0x01;break;
    case 12: PORTC=0x08;break;
    case 13: PORTC=0x02;break;
    case 14: PORTC=0x04;break;

    case 21: PORTC=0x01;break;
    case 22: PORTC=0x08;break;
    case 23: PORTC=0x02;break;
    case 24: PORTC=0x04;break;
    case 31: PORTC=0x09;break;
    case 32: PORTC=0x0A;break;
    case 33: PORTC=0x06;break;
    case 34: PORTC=0x05;break;

    }

    delay_ms(dt2);    
  }
}

void motorOff(void){
  PORTC = 0x00;   
}

void fullStep(int cnt, char forwards){
  int i=0;
  for (i = 0; i < cnt; i++){
    duty = 50;
    if (forwards == 'R')
      {
      int j=0;
      for (j = 1; j <= 4; j++){
        doStep(j);
        }
      }
    else if (forwards == 'L')
      {
      int j=0;
      for (j = 4; j >= 1; j--){
        doStep(j);
        }
      }
    }
}

void halfStep(int cnt, char forwards){
  const int list[] = {1,11,2,12,3,13,4,14};
  int i=0;
  for (i = 0; i < cnt; i++){
    duty = 50;
    if (forwards == 'R')
      {
      int j=0;
      for (j = 0; j <= 7; j++){
        doStep(list[j]);
        }
      }
    else if(forwards == 'L')
      {
      int j=0;
      for (j = 7; j >= 0; j--){
        doStep(list[j]);
        }
      }
  }
}

void u16Step(int cnt, char forwards){

  const int list[] = {1,21,11,31,2,22,12,32,3,23,13,33,4,24,14,34};
  int i=0;
  for (i = 0; i < cnt; i++){
    duty = 50;
    if (forwards == 'R')
      {
      int j=0;
      for (j = 0; j <= 15; j++){
        doStep(list[j]);
        }
      }
    else if(forwards == 'L')
      {
      int j=0;
      for (j = 15; j >= 0; j--){
        doStep(list[j]);
        }
      }
  }  
}
  
void u24Step(int cnt, char forwards){
  const int list1[] = {1,11,2,12,3,13,4,14};
  const int list2[] = {21,31,22,32,23,33,24,34};
   int i=0;
  for (i = 0; i < cnt; i++){

    duty = 50;
    if (forwards == 'R')
      {
      int j=0;
      for (j = 0; j <= 7; j++){
        doStep(list1[j]);
          if (forwards == 'R'){
            duty = 66;   doStep(list2[j]);
            duty = 33;   doStep(list2[j]);
        }
          else if(forwards == 'L'){
            duty = 33;   doStep(list2[j]);
            duty = 66;   doStep(list2[j]);
        }
      }
      }
    else if(forwards == 'L')
      {
      int j=0;
      for (j = 7; j >= 0; j--){
      if (forwards == 'R'){
            duty = 66;   doStep(list2[j]);
            duty = 33;   doStep(list2[j]);
        }
          else if(forwards == 'L'){
            duty = 33;   doStep(list2[j]);
            duty = 66;   doStep(list2[j]);
        }
        doStep(list1[j]);
        }
      }
     
  }
}
void u32Step(int cnt, char forwards){
  const int list1[] = {1,11,2,12,3,13,4,14};
  const int list2[] = {21,31,22,32,23,33,24,34};
   int i=0;
  for (i = 0; i < cnt; i++){

    duty = 50;
    if (forwards == 'R')
      {
      int j=0;
      for (j = 0; j <= 7; j++){
      doStep(list1[j]); 
      if (forwards == 'R'){
        duty = 75;    doStep(list2[j]);
        duty = 50;    doStep(list2[j]);
        duty = 25;    doStep(list2[j]);
        }
      else if (forwards == 'L'){
        duty = 25;    doStep(list2[j]);
        duty = 50;    doStep(list2[j]);
        duty = 75;    doStep(list2[j]);
      }
      }
      }
    else if(forwards == 'L')
      {
      int j=0;
      for (j = 7; j >= 0; j--){
      if (forwards == 'R'){
        duty = 75;    doStep(list2[j]);
        duty = 50;    doStep(list2[j]);
        duty = 25;    doStep(list2[j]);
        }
      else if (forwards == 'L'){
        duty = 25;    doStep(list2[j]);
        duty = 50;    doStep(list2[j]);
        duty = 75;    doStep(list2[j]);
      }
      doStep(list1[j]);
      }
      }
     
  }
}

void u48Step(int cnt, char forwards){
  const int list1[] = {1,11,2,12,3,13,4,14};
  const int list2[] = {21,31,22,32,23,33,24,34};
  long i=0;
  for (i = 0; i < cnt; i++){

    duty = 50;
    if (forwards == 'R')
      {
      int j=0;
      for (j = 0; j <= 7; j++){
        doStep(list1[j]); 
        if (forwards == 'R'){
          for (i = 5; i >= 1; i--){duty = 17 * i; doStep(list2[j]);}
        }
        else if(forwards == 'L'){
          for (i = 1; i <= 5; i++){duty = 17 * i; doStep(list2[j]);}
        }
        }
      }
    else if(forwards == 'L')
      {
      int j=0;
      for (j = 7; j >= 0; j--){
        if (forwards == 'R'){
          for (i = 5; i >= 1; i--){duty = 17 * i; doStep(list2[j]);}
        }
        else if(forwards == 'L'){
          for (i = 1; i <= 5; i++){duty = 17 * i; doStep(list2[j]);}
        } 
        doStep(list1[j]);
        }
      }
     
  }
}

void u64Step(int cnt, char forwards){
  const int list1[] = {1,11,2,12,3,13,4,14};
  const int list2[] = {21,31,22,32,23,33,24,34};
  long i=0;
  for (i = 0; i < cnt; i++){

    duty = 50;
    if (forwards == 'R')
      {
      int j=0;
      for (j = 0; j <= 7; j++){
        doStep(list1[j]); 
        if (forwards == 'R'){
          for (i = 7; i >= 1; i--){duty = 12 * i; doStep(list2[j]);}
        }
        else if(forwards == 'L'){
          for (i = 1; i <= 7; i++){duty = 12 * i; doStep(list2[j]);}
        }
        }
      }
    else if(forwards == 'L')
      {
      int j=0;
      for (j = 7; j >= 0; j--){
        if (forwards == 'R'){
          for (i = 7; i >= 1; i--){duty = 12 * i; doStep(list2[j]);}
        }
        else if(forwards == 'L'){
          for (i = 1; i <= 7; i++){duty = 12 * i; doStep(list2[j]);}
        } 
        doStep(list1[j]);
        }
      }
     
  }
}     

void u96Step(int cnt, char forwards){
  const int list1[] = {1,11,2,12,3,13,4,14};
  const int list2[] = {21,31,22,32,23,33,24,34};
  long i=0;
  //int i=0;
  for (i = 0; i < cnt; i++){

    duty = 50;
    if (forwards == 'R')
      {
      int j=0;
      for (j = 0; j <= 7; j++){
        doStep(list1[j]); 
        if (forwards == 'R'){
        //int i=0;
        for (i = 9; i >= 1; i--){
         duty = 10 * i; doStep(list2[j]);
        }
       }
        else if(forwards == 'L'){
        //int i=0;
        for (i = 1; i <= 9; i++){
        duty = 10 * i; doStep(list2[j]);
        }
       }
      }
      }
    else if(forwards == 'L')
      {
      int j=0;
      for (j = 7; j >= 0; j--){
        long i=0;
        if (forwards == 'R'){
        //int i=0;
        for (i = 9; i >= 1; i--){
         duty = 10 * i; doStep(list2[j]);
        }
       }
        else if(forwards == 'L'){
        //int i=0;
        for (i = 1; i <= 9; i++){
        duty = 10 * i; doStep(list2[j]);
        }
       } 
        doStep(list1[j]);
        }
      }
     
  }
}    
