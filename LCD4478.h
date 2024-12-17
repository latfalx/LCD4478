#ifndef _LCD4478_H_
#define _LCD4478_H_
#include <avr/io.h> 
#include <avr/pgmspace.h>
#include <util/delay.h>
#include "LCD4478_Instruction.h"

/** Для вывода на дисплей с printf() из библиотеки stdio.h 
 *  Для отключение необходимо закомментировать USE_PRINTF
 *  вывод на дисплей будет осуществляться с помощью команд:
 *  LCD4478_PrintCP для кодировки CP1251
 *  LCD4478_PrintUTF для кодироки UTF */
#define USE_PRINTF

/* Определение для работы с printf() из библиотеки stdio.h */
#ifdef USE_PRINTF
    #include <stdio.h>
    //#define CP_SYMBOL /* Включение/Отключение кодировки CP1251  */
    #define UTF_SYMBOL  /* Включение/Отключение кодировки UTF  */
#endif /* USE_PRINTF */

/*  Установить на указаный порт и указаный пин порта: 1  */
#define SETBIT(PORT, PIN)  PORT |= (1<<PIN)
/*  Установить на указаный порт и указаный пин порта: 0  */
#define CLRBIT(PORT, PIN)  PORT &= ~(1<<PIN)

#define LCD4478_PORT	PORTA   /*  Назначение порта    */
#define LCD4478_DDR	DDRA    /*  Регистр управления порта    */
#define LCD4478_EN      PA5     /*  Стробирующий сигнал */
#define LCD4478_RW      PA4		/*  Данные/Инструкции(команды)  */
#define LCD4478_RS      PA7		/*  Читать/Записать на экран    */
#define LCD4478_DB4     PA2     /*  DB4 подключен к 2 пину порта PORTA  */
#define LCD4478_DB5     PA3     /*  DB5 подключен к 3 пину порта PORTA  */
#define LCD4478_DB6     PA0     /*  DB6 подключен к 0 пину порта PORTA  */
#define LCD4478_DB7     PA1     /*  DB7 подключен к 1 пину порта PORTA  */

/*  Инициализация пинов порта на запись (DDR)    */
#define LCD4478_PORT_WRITE()	LCD4478_DDR = 0b11111111
/*  Инициализация пинов порта на чтение (DDR)    */
#define LCD4478_PORT_READ()	    LCD4478_DDR = 0b11110000

/*  Установить бит RW в 1 для чтения с LCD4478   */
#define LCD4478_READ()	SETBIT(LCD4478_PORT, LCD4478_RW)
/*  Установить бит RW в 0 для записи в LCD4478   */
#define LCD4478_WRITE()	CLRBIT(LCD4478_PORT, LCD4478_RW)

/*  Установить бит RS в 1 для отправки данных в LCD4478  */
#define LCD4478_DATA()	SETBIT(LCD4478_PORT, LCD4478_RS)
/*  Установить бит RS в 0 для отправки команд в LCD4478  */
#define LCD4478_INSTRUCTION()	CLRBIT(LCD4478_PORT, LCD4478_RS)

/*	Подключается к LCD4478 и настраивает его для отображения	*/
void LCD4478_Setup(void);
/*	Отправляем команду на LCD4478	*/
void LCD4478_Command(uint8_t byte);
/*  Очищает весь дисплей и устанавливает адрес DDRAM в 0.   */
void LCD4478_Clear(void);
/** Установить координаты печати
 *  line: номер строки (1/2)
 *  offset: смещение в строке (от 0 до 39)    */
void LCD4478_XY(uint8_t line, uint8_t offset);

#ifndef USE_PRINTF
/** Вывод строки в CP1251 с русскими символами	
 *  line: номер строки (1/2)
 *  offset: смещение в строке (от 0 до 39)    */
void LCD4478_PrintCP(uint8_t line, uint8_t offset, char *pointer);
/** Вывод строки в Unicode-8 на LCD4478	по координатам.
 *  line: номер строки (1/2)
 *  offset: смещение в строке (от 0 до 39)    */
void LCD4478_PrintUTF(uint8_t line, uint8_t offset, char *pointer);
#endif /* USE_PRINTF  */

#endif /* _LCD4478_H_ */ 
