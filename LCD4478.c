#include "LCD4478.h"
/*	Русские символы	*/
const PROGMEM uint8_t LCD4478_RUS[] ={
 	0x41,0xA0,0x42,0xA1,0xE0,0x45,0xA3,0xA4,  /*	АБВГДЕЖЗ	*/
 	0xA5,0xA6,0x4B,0xA7,0x4D,0x48,0x4F,0xA8,  /*	ИЙКЛМНОП	*/
 	0x50,0x43,0x54,0xA9,0xAA,0x58,0xE2,0xAB,  /*	РСТУФХЦЧ	*/
 	0xAC,0xE2,0xAD,0xAE,0x62,0xAF,0xB0,0xB1,  /*	ШЩЪЫЬЭЮЯ	*/
 	0x61,0xB2,0xB3,0xB4,0xE3,0x65,0xB6,0xB7,  /*	абвгдежз	*/
 	0xB8,0xB9,0xBA,0xBB,0xBC,0xBD,0x6F,0xBE,  /*	ийклмноп	*/
 	0x70,0x63,0xBF,0x79,0xE4,0x78,0xE5,0xC0,  /*	рстуфхцч	*/
 	0xC1,0xE6,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7   /*	шщъыьэюя	*/
};
/*	Дополнительные символы	*/
const PROGMEM uint8_t LCD4478_CGRAM[] ={
	0x00,0x00,0x00,0x00,0x01,0x0A,0x04,0x00,	/*	Cимвол '\x8': Выбрать	*/
	0x00,0x00,0x00,0x00,0x0F,0x0F,0x0F,0x00,	/*	Cимвол '\x1': Стоп		*/
	0x00,0x00,0x00,0x00,0x04,0x0E,0x1F,0x00,	/*	Cимвол '\x2': Вверх		*/
	0x00,0x00,0x00,0x00,0x1F,0x0E,0x04,0x00,	/*	Cимвол '\x3': Вниз		*/
	0x00,0x00,0x00,0x00,0x00,0x0E,0x00,0x00,	/*	Cимвол '\x4': Минус		*/
	0x00,0x00,0x00,0x00,0x04,0x0E,0x04,0x00,	/*	Cимвол '\x5': Плюс		*/
};						

/*	Настройка вывода printf() для определенной кодировки	*/
#ifdef CP_SYMBOL
	static int LCD4478_PrintfCP(char sym, FILE* stream);
	static FILE lcd4478_stdout = FDEV_SETUP_STREAM(LCD4478_PrintfCP, NULL, _FDEV_SETUP_WRITE);
#endif /* CP_SYMBOL */
#ifdef UTF_SYMBOL
	static int LCD4478_PrintfUTF(char sym, FILE* stream);
	static FILE lcd4478_stdout = FDEV_SETUP_STREAM(LCD4478_PrintfUTF, NULL, _FDEV_SETUP_WRITE);
#endif /* UTF_SYMBOL */

/*	Отправка на дисплей стробирующего сигнала	*/
void LCD4478_SendPulse(void)
{				
	CLRBIT(LCD4478_PORT, LCD4478_EN);									
	_delay_us(1);	/*	Ждем 1мкс	*/
	SETBIT(LCD4478_PORT, LCD4478_EN);
	_delay_us(1);	/*	Ждем > 450нс	*/
	CLRBIT(LCD4478_PORT, LCD4478_EN);							
	_delay_us(100);	/*	Ждем > 37мкс	*/
}
/*	Отпраляем из байта только 4 младших бита (для работы по 4 пинам)	*/
void LCD4478_Send4bit(uint8_t byte)
{
	/*	Сравниваем младшие разряды байта при совпадении устанавливаем соответствующие пины	*/
	if (byte & 0x01)	/*	1 бит	*/
		SETBIT(LCD4478_PORT, LCD4478_DB4);
		else 
			CLRBIT(LCD4478_PORT, LCD4478_DB4);
   	if (byte & 0x02)	/*	2 бит	*/
		SETBIT(LCD4478_PORT, LCD4478_DB5);
		else 
			CLRBIT(LCD4478_PORT, LCD4478_DB5);
	if (byte & 0x04)	/*	3 бит	*/
		SETBIT(LCD4478_PORT, LCD4478_DB6);
		else 
			CLRBIT(LCD4478_PORT, LCD4478_DB6);
	if (byte & 0x08)	/*	4 бит	*/
		SETBIT(LCD4478_PORT, LCD4478_DB7);
		else
			CLRBIT(LCD4478_PORT, LCD4478_DB7);
	/*	Установили биты теперь отправляем импульс для передачи	*/	
	LCD4478_SendPulse();    
}
/*	Отправляем байт данных на LCD4478	*/
void LCD4478_SendByte(uint8_t byte)
{
	/*	Настраиваем для отправки данных	*/
	LCD4478_WRITE();
	LCD4478_DATA();
	LCD4478_Send4bit(byte>>4);	/*	Отправляем старшие разряды байта	*/
	LCD4478_Send4bit(byte);	/*	Отправляем младшие разряды байта	*/
}

void LCD4478_Command(uint8_t byte)
{
	/*	Настраиваем для отправки комманд	*/
	LCD4478_WRITE();                     
	LCD4478_INSTRUCTION();
	LCD4478_Send4bit(byte>>4);	/*	Отправляем старшие разряды байта	*/
	LCD4478_Send4bit(byte);	/*	Отправляем младшие разряды байта	*/
}

void LCD4478_Clear(void)
{                                                   
	LCD4478_Command(LCD4478_DISPLAY_CLEAR);
	_delay_us(1600);	/*	Ждем > 1,52мс	*/     
}
/*	Инициализация 4 битового режима работы для LCD4478	*/
void LCD4478_Init4bitMode(void)
{
	_delay_ms(50);	/*	Ждем > 40мс после включения экрана	*/
	/*	Устанавливаем пины управления	*/
	LCD4478_WRITE();                            
	LCD4478_INSTRUCTION();
	CLRBIT(LCD4478_PORT, LCD4478_EN);	/*  Стробирующий сигнал для LCD4478 установить в 0  */
	/*	Начало установки режима 4 бит	*/
	LCD4478_Send4bit(LCD4478_MODE_4BIT);   
	_delay_us(4500);	/*	Ждем > 4.1мс	*/
	LCD4478_Send4bit(LCD4478_MODE_4BIT);          
	_delay_us(150);		/*	Ждем > 100мкс	*/
	LCD4478_Send4bit(LCD4478_MODE_4BIT);	
	/*	Конец установки режима 4 бит  
	*	Установить интерфейс длиной 8 бит	*/
	LCD4478_Send4bit(LCD4478_MODE_TWICE_4BIT);
	LCD4478_Command(LCD4478_FUNCTION_SET | LCD4478_FUNCTION_4BIT| LCD4478_FUNCTION_2LINE | LCD4478_FUNCTION_5x8DOTS);
	LCD4478_Command(LCD4478_DISPLAY_SET | LCD4478_DISPLAY_OFF);
	LCD4478_Clear();
	LCD4478_Command(LCD4478_ENTRY_SET | LCD4478_ENTRY_INCREMENT | LCD4478_ENTRY_SHIFT_DISPLAY_OFF);
}
/*	Загрузка дополнительных символов в CGRAM	*/
void LCD4478_LoadSymbols(void)
{
	LCD4478_Command(LCD4478_CGRAM_SET);
	/*	Указатель на массив данных для CGRAM	*/
	PGM_P pointer = (PGM_P)LCD4478_CGRAM;
	for(uint8_t i=0; i < sizeof(LCD4478_CGRAM); i++)
	{
		uint8_t byte = pgm_read_byte(pointer + i);
		LCD4478_SendByte(byte);
		_delay_ms(10);
	}
}

void LCD4478_Setup(void)
{
	LCD4478_PORT_WRITE();
	LCD4478_Init4bitMode();
	LCD4478_Command(LCD4478_DISPLAY_SET | LCD4478_DISPLAY_ON);
	LCD4478_LoadSymbols();
	LCD4478_Command(LCD4478_DDRAM_SET | LCD4478_DDRAM_1LINE);
	#ifdef USE_PRINTF
		stdout = &lcd4478_stdout;
	#endif /* USE_PRINTF */
	
}

void LCD4478_XY(uint8_t line, uint8_t offset)
{
	/*	Установка адреса для печати	*/
	if (offset > 39)
		offset = 0;
	switch(line)
	{
		case 0: break;
		case 1:	LCD4478_Command((LCD4478_DDRAM_SET | LCD4478_DDRAM_1LINE) + offset); break;
		case 2:	LCD4478_Command((LCD4478_DDRAM_SET | LCD4478_DDRAM_2LINE) + offset); break;
		default: break;
	}
}

/* Обработчики которые выводят символы на дисплей*/
#ifdef USE_PRINTF
	#ifdef CP_SYMBOL
	/*	Обработчик символов в кодировке CP1251 для printf()	*/
	static int LCD4478_PrintfCP(char sym, FILE *stream)
	{
		if (sym == '\r')
		{
			LCD4478_XY(1,0);
			return 0;
		}
		if (sym == '\n')
		{
			LCD4478_XY(2,0);
			return 0;
		}
		if (sym == '\x8')
		{
			LCD4478_SendByte(0x00);
			return 0;
		}
		if((uint8_t) sym >= 192)
		{
			LCD4478_SendByte(pgm_read_byte(&LCD4478_RUS[(uint8_t) sym - 192]));
			return 0;
		}
		LCD4478_SendByte((uint8_t) sym);
		return 0;
	}
	#endif /* CP_SYMBOL */
	#ifdef UTF_SYMBOL
	/*	Обработчик символов в кодировке UTF для printf()	*/
	static int LCD4478_PrintfUTF(char sym, FILE* stream)
	{
		if (sym == '\r')
		{
			LCD4478_XY(1,0);
			return 0;
		}	
		if (sym == '\n')
		{
			LCD4478_XY(2,0);
			return 0;
		}
		if (sym == '\x8')
		{
			LCD4478_SendByte(0x00);
			return 0;
		}
		if ((uint8_t) sym == 208 || (uint8_t) sym == 209)
		{
			return 0;
		}
		if ((uint8_t) sym >= 144 && (uint8_t) sym <= 191)
		{
				LCD4478_SendByte(pgm_read_byte(&LCD4478_RUS[(uint8_t) sym - 144]));
				return 0;
		}
		if ((uint8_t) sym >= 128 && (uint8_t) sym <= 143)
		{
				LCD4478_SendByte(pgm_read_byte(&LCD4478_RUS[(uint8_t) sym - 80]));
				return 0;
		}
		if ((uint8_t) sym != 0x00)
		{
				LCD4478_SendByte((uint8_t) sym);
				return 0;
		}
		return 0;
	}
	#endif /* UTF_SYMBOL */
#else
	void LCD4478_PrintCP(uint8_t line, uint8_t offset, char *string)
	{
		LCD4478_XY(line,offset);
		/*	Проверка символов	*/
		while((uint8_t) *string)
		{
			if((uint8_t) *string >= 192) 
				LCD4478_SendByte(pgm_read_byte(&LCD4478_RUS[(uint8_t) *string - 192]));
			else
				if((uint8_t) *string != 0x00) 
					LCD4478_SendByte((uint8_t) *string);
			string++;
		}
	}
	void LCD4478_PrintUTF(uint8_t line, uint8_t offset, char *string)
	{
		LCD4478_XY(line,offset);
		/*	Проверка символов	*/
		while ((uint8_t) *string)
		{
			/*	Первый байт пропускаем	*/
			if ((uint8_t) *string == 208 || (uint8_t) *string == 209)
			{
				string++;
				/*	Проверям второй байт*/
				if ((uint8_t) *string >= 144 && (uint8_t) *string <= 191) 
					LCD4478_SendByte(pgm_read_byte(&LCD4478_RUS[(uint8_t) *string - 144]));
				else
					if ((uint8_t) *string >= 128 && (uint8_t) *string <= 143) 
						LCD4478_SendByte(pgm_read_byte(&LCD4478_RUS[(uint8_t) *string - 80]));
			}
			else 
				if((uint8_t) *string != 0x00) 
					LCD4478_SendByte((uint8_t) *string);
			string++;	
		}
	}
#endif /* USE_PRINTF */
