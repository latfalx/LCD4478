# Example using LCD4478
```
#define F_CPU 8000000L
#include <avr/io.h>
#include <util/delay.h>
#include "LCD4478.c"
int main(void){
	LCD4478_Setup();
	while(1){
		//--------------------------------/	Температура
		LCD4478_Clear();
		LCD4478_PrintCP(1,3,"Температура");
		LCD4478_PrintCP(2,5,"+ 25");
		LCD4478_Print(0x00);
		LCD4478_PrintCP(2,10,"C");
		_delay_ms(2000);
		//--------------------------------/	Влажность
		LCD4478_Clear();
		LCD4478_PrintCP(1,4,"Влажность");
		LCD4478_PrintCP(2,7,"40");
		LCD4478_PrintCP(2,9,"%");
		_delay_ms(2000);
	}
}
```
