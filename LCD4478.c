#include "LCD4478.h"
#include <avr/pgmspace.h>
//--------------------------------/ Русский символьный массив 
const PROGMEM char LCD4478_RUS[] ={
 0x41,0xA0,0x42,0xA1,0xE0,0x45,0xA3,0xA4,  //АБВГДЕЖЗ
 0xA5,0xA6,0x4B,0xA7,0x4D,0x48,0x4F,0xA8,  //ИЙКЛМНОП
 0x50,0x43,0x54,0xA9,0xAA,0x58,0xE2,0xAB,  //РСТУФХЦЧ
 0xAC,0xE2,0xAD,0xAE,0x62,0xAF,0xB0,0xB1,  //ШЩЪЫЬЭЮЯ
 0x61,0xB2,0xB3,0xB4,0xE3,0x65,0xB6,0xB7,  //абвгдежз
 0xB8,0xB9,0xBA,0xBB,0xBC,0xBD,0x6F,0xBE,  //ийклмноп
 0x70,0x63,0xBF,0x79,0xE4,0x78,0xE5,0xC0,  //рстуфхцч
 0xC1,0xE6,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7   //шщъыьэюя
};	
//--------------------------------/ Дополнительные символы	
const PROGMEM unsigned char LCD4478_CGRAM[] ={
	// символ 0: Градус
	0x06,    /*  .....$$.  */
	0x09,    /*  ....$..$  */
	0x09,    /*  ....$..$  */
	0x06,    /*  .....$$.  */
	0x00,    /*  ........  */
	0x00,    /*  ........  */
	0x00,    /*  ........  */
	0x00,    /*  ........  */
	// символ 1: Минус
	0x00,    /*  ........  */
	0x00,    /*  ........  */
	0x00,    /*  ........  */
	0x07,    /*  .....$$$  */
	0x00,    /*  ........  */
	0x00,    /*  ........  */
	0x00,    /*  ........  */
	0x00,    /*  ........  */
	// символ 2: Плюс
	0x00,    /*  ........  */
	0x00,    /*  ........  */
	0x02,    /*  ......$.  */
	0x07,    /*  .....$$$  */
	0x02,    /*  ......$.  */
	0x00,    /*  ........  */
	0x00,    /*  ........  */
	0x00,    /*  ........  */
};						
//--------------------------------/ Стробирующий сигнал
void LCD4478_PulseSend(){							
	LCD4478_EN_0;														
	_delay_us(1);	// 1мкс
    LCD4478_EN_1;
	_delay_us(1);	// > 450нс
	LCD4478_EN_0;													
	_delay_us(100);	// Нужно > 37мкс
}
//--------------------------------/	Из байта, 4 младших бита переходят в старшие на LCD
void LCD4478_Write4bit(unsigned char lcd4byte){
	if (lcd4byte & 0x01) LCD4478_DB4_1;
	else LCD4478_DB4_0;
    if (lcd4byte & 0x02) LCD4478_DB5_1;
	else LCD4478_DB5_0;
    if (lcd4byte & 0x04) LCD4478_DB6_1;
	else LCD4478_DB6_0;
    if (lcd4byte & 0x08) LCD4478_DB7_1;
	else LCD4478_DB7_0;		
    LCD4478_PulseSend();    
} 
//--------------------------------/	Отправляем команду, байт по 4бита = 2 отправки 
void LCD4478_Command(unsigned char lcdbyte){                           
	LCD4478_RS_0;
    LCD4478_Write4bit(lcdbyte>>4);
    LCD4478_Write4bit(lcdbyte);
}
//--------------------------------/	Очистка экрана
void LCD4478_Clear(){                                                   
    LCD4478_Command(LCD4478_CLEARDISPLAY);
	_delay_us(1600);							// Ждем > 1,52мс     
}
//--------------------------------/	Отправляем данные байт / 4бита = 2 отправки
void LCD4478_Print(unsigned char lcdbyte){
	LCD4478_RS_1;
    LCD4478_Write4bit(lcdbyte>>4);
    LCD4478_Write4bit(lcdbyte);
}
//--------------------------------/	Инициализация 4 битового режима
void LCD4478_Init4bitMode(){
	_delay_ms(50);								// Ждем > 40мс после включения экрана.
	LCD4478_RW_0;								// Обнуляем пины управления                                
    LCD4478_RS_0;
    LCD4478_EN_0;
    LCD4478_Write4bit(LCD4478_4BITMODE);		// Начало установки режима 4 бит     
	_delay_us(4500);							// Ждем > 4.1мс
    LCD4478_Write4bit(LCD4478_4BITMODE);          
	_delay_us(150);								// Ждем > 100мкс
    LCD4478_Write4bit(LCD4478_4BITMODE);		// Конец установки режима 4 бит  
    LCD4478_Write4bit(LCD4478_2x4BITMODE);		// Установить интерфейс длиной 8 бит.            
    LCD4478_Command(LCD4478_FUNCTIONSET |       // Установить функцию          
                    LCD4478_2LINE |             // Две строки
                    LCD4478_5x8DOTS);           // Отображение 5х8 точек               
    LCD4478_Command(LCD4478_DISPLAYCONTROL |    // Установить дисплей
                    LCD4478_DISPLAYOFF);        // Выключить дисплей
    LCD4478_Clear();
    LCD4478_Command(LCD4478_ENTRYMODESET |      // Установить вход
                    LCD4478_ENTRYINCREMENT |    // Инкрементирован вход
                    LCD4478_ENTRYSHIFTRIGHT);   // Изменение в право
}
//--------------------------------/	Загрузка символов в CGRAM
void LCD4478_LoadSymbol(){
	LCD4478_Command(LCD4478_SETCGRAM);		// Установка адреса для записи
	PGM_P pointer = (PGM_P)LCD4478_CGRAM;	// Получение указателя
	for(unsigned char i=0; i < sizeof(LCD4478_CGRAM); i++){           
		unsigned char byte = pgm_read_byte(pointer + i);
		LCD4478_Print(byte);
		_delay_ms(10);
	}
}
//--------------------------------/	Аналог Print для Unicode с русскими символами
void LCD4478_PrintUTF(unsigned short line, unsigned short offset, char *ptr){
	switch(line){						// Установка адреса для печати
		case 0: break;
		case 1:	LCD4478_Command((LCD4478_SETDDRAM | LCD4478_DDRAM_1LINE) + offset); break;
		case 2:	LCD4478_Command((LCD4478_SETDDRAM | LCD4478_DDRAM_2LINE) + offset); break;
		default: break;
	}
    unsigned char sym;
    for (int i=0; 1; i++){
        sym=ptr[i];
        if(sym==208 || sym==209){
            i++;
            sym=ptr[i];
            if(sym>=144 && sym<=191) 
				LCD4478_Print(pgm_read_byte(&LCD4478_RUS[sym-144]));
            else if(sym>=128 && sym<=143) 
				LCD4478_Print(pgm_read_byte(&LCD4478_RUS[sym-80]));
		}
        else if(sym!=0x00) 
            LCD4478_Print(sym);
        else break;
	}
}
//--------------------------------/	Аналог Print для CP1251 с русскими символами
void LCD4478_PrintCP(unsigned short line, unsigned short offset, char *ptr){
	switch(line){						// Установка адреса для печати
		case 0: break;
		case 1:	LCD4478_Command((LCD4478_SETDDRAM | LCD4478_DDRAM_1LINE) + offset); break;
		case 2:	LCD4478_Command((LCD4478_SETDDRAM | LCD4478_DDRAM_2LINE) + offset); break;
		default: break;
	}
	unsigned char sym;
	for (int i=0; 1; i++){
		sym=ptr[i];
		if(sym>=192 && sym<=255) 
			LCD4478_Print(pgm_read_byte(&LCD4478_RUS[sym-192]));
		else if(sym!=0x00) 
			LCD4478_Print(sym);
		else break;
	}
	
}
//--------------------------------/	Установка LCD4478
void LCD4478_Setup(){
    LCD4478_InitPinMode;												 // Инициализация пинов
    LCD4478_Init4bitMode();                                              // Инициализация 4 битного режима
    LCD4478_Command(LCD4478_DISPLAYCONTROL | LCD4478_DISPLAYON);         // Включение дисплея
    LCD4478_LoadSymbol();                                                // Загрузка других символов в CGRAM
    LCD4478_Command(LCD4478_SETDDRAM | LCD4478_DDRAM_1LINE);             // Установка адреса для печати	
}
