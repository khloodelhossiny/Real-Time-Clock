/*
 * clock_sys.c
 *
 * Created: 12/26/2022 11:46:12 AM
 * Author : Ve-ga
 */ 

#include "lcd.h"
#include "seven_seg.h"
#include "Timer0.h"
#include "External_Interrupts.h"

static int8_t second = 0, minut = 0, hour = 0, clock_on = 1;
int8_t key , lst_minut = -1 , lst_hour = -1, count_press = -1;

void clock_control();

int main(void)
{
	LCD_init();
    seven_seg_init();
	Timer0_normal_init();
	SETBIT(DDRD, 2);
	SETBIT(DDRD, 1);
	SETBIT(DDRD, 0);	
	INT0_init();
	LCD_write_command(0x82);
	LCD_write_char(':');
	LCD_write_command(0x85);
	LCD_write_char(':');
	
    while (1) 
    {	
		if(second == 60){
			second = 0;
			minut ++;
			
			if(minut == 60){
				minut = 0;
				hour ++;
				
				if(hour == 24){
					hour = 0;
				}
			}
		}
		LCD_write_command(0x86);
		LCD_write_char(second / 10 + '0');
		LCD_write_command(0x87);
		LCD_write_char(second % 10 + '0');
		
		if( lst_minut != minut){
			LCD_write_command(0x83); 
			LCD_write_char(minut / 10 + '0');
			LCD_write_command(0x84);
			LCD_write_char(minut % 10 + '0');
			lst_minut = minut;
		}
		if(lst_hour != hour){
			LCD_write_command(0x80);
			LCD_write_char(hour / 10 + '0');
			LCD_write_command(0x81);
			LCD_write_char(hour % 10 + '0');
			lst_hour = hour;
		}
		if(clock_on == 0){
 			LCD_write_command(0xc0);
 			LCD_write_string("OFF");
			 
 			clock_control();
			clock_on = 1;
			LCD_write_command(0xc2);
			LCD_write_char(' ');
			LCD_write_command(0xc0);
			LCD_write_string("ON");
			
		}					
    }
	
}
ISR(TIMER0_OVF_vect){
	static uint16_t count = 0 ;
	static uint8_t h = 0, m = 0, s = 0;
	if(clock_on == 1){
		count ++;
	}
	if(count == 976){ // 16 * 64 * ? = 1000000       => 1sec
		second ++;
		count = 0;
	}
	switch (h){
		case 0:	seven_seg_write(hour / 10, 1);	break;
		case 1:	seven_seg_write(hour % 10, 2);	break;
		case 2: seven_seg_write(minut / 10, 3);	break;
		case 3:	seven_seg_write(minut % 10, 4);	break;
		case 4:	seven_seg_write(second / 10 ,5);break;
		case 5:	seven_seg_write(second % 10, 6);break;
	}
	h++;
	if( h == 6){
		h = 0;
	}
	
}
ISR(INT0_vect){
	if(count_press == 0){
		clock_on = 0;
	}
	count_press ++;

	
}
void clock_control(){
	
	while(1){
		if(count_press == 1){
			if(READBIT(PIND, 0) == 1){
				while(READBIT(PIND, 0) == 1);
				hour ++;
				if(hour >= 24){
					hour = 0;
				}
			}
			else if(READBIT(PIND, 1) == 1){
				while(READBIT(PIND, 1) == 1);
				hour --;
				if(hour < 0){
					hour = 23;
				}
			}
			LCD_write_command(0x80);
			LCD_write_char(hour / 10 + '0');
			LCD_write_command(0x81);
			LCD_write_char(hour % 10 + '0');
		}
		else if(count_press == 2){
			if(READBIT(PIND, 0) == 1){
				while(READBIT(PIND, 0) == 1);
				minut ++;
				if(minut >= 60){
					minut = 0;
				}
			}
			else if(READBIT(PIND, 1) == 1){
				while(READBIT(PIND, 1) == 1);
				minut --;
				if(minut < 0){
					minut = 59;
				}
			}
			LCD_write_command(0x83); 
			LCD_write_char(minut / 10 + '0');
			LCD_write_command(0x84);
			LCD_write_char(minut % 10 + '0');
		}
		else{
			if(READBIT(PIND, 0) == 1){
				while(READBIT(PIND, 0) == 1);
				second ++;
				if(second >= 60){
					second = 0;
				}
			}
			else if(READBIT(PIND, 1) == 1){
				while(READBIT(PIND, 1) == 1);
				second --;
				if(second < 0){
					second = 59;
				}
			}
			LCD_write_command(0x86); 
			LCD_write_char(second / 10 + '0');
			LCD_write_command(0x87);
			LCD_write_char(second % 10 + '0');
		}
		if( count_press > 3){
			count_press = 0;
			clock_on = 1;
			return;
		}
	}
}

