//--------------------------------/ Назначение порта /--------------------------------
#define LCD4478_PORT    PORTD                                      // Назначение порта
#define LCD4478_DDR     DDRD                               // Регистр управления порта
#define LCD4478_EN      PD0                                     // Стробирующий сигнал
#define LCD4478_RW      PD1                              // Данные/Инструкции(команды)
#define LCD4478_RS      PD2                                // Читать/Записать на экран
#define LCD4478_DB4     PD4                                      // Старший бит данных
#define LCD4478_DB5     PD5                                      // Старший бит данных
#define LCD4478_DB6     PD6                                      // Старший бит данных
#define LCD4478_DB7     PD7                                      // Старший бит данных
//------------------------------------------------------------------------------------
#define LCD4478_SETBIT(LCD4478_PORT, LCD4478_OFFSET_BIT)  LCD4478_PORT |= (1<<LCD4478_OFFSET_BIT)
#define LCD4478_CLRBIT(LCD4478_PORT, LCD4478_OFFSET_BIT)  LCD4478_PORT &= ~(1<<LCD4478_OFFSET_BIT)
//------------------------------------------------------------------------------------
#define LCD4478_EN_1	LCD4478_SETBIT(LCD4478_PORT, LCD4478_EN)			                
#define LCD4478_EN_0	LCD4478_CLRBIT(LCD4478_PORT, LCD4478_EN)				                
#define LCD4478_RW_1	LCD4478_SETBIT(LCD4478_PORT, LCD4478_RW)				              
#define LCD4478_RW_0	LCD4478_CLRBIT(LCD4478_PORT, LCD4478_RW)				             
#define LCD4478_RS_1	LCD4478_SETBIT(LCD4478_PORT, LCD4478_RS)				             
#define LCD4478_RS_0	LCD4478_CLRBIT(LCD4478_PORT, LCD4478_RS)				             
//------------------------------------------------------------------------------------
#define LCD4478_DB4_1	LCD4478_SETBIT(LCD4478_PORT, LCD4478_DB4)				             
#define LCD4478_DB4_0	LCD4478_CLRBIT(LCD4478_PORT, LCD4478_DB4)				             
#define LCD4478_DB5_1	LCD4478_SETBIT(LCD4478_PORT, LCD4478_DB5)				             
#define LCD4478_DB5_0	LCD4478_CLRBIT(LCD4478_PORT, LCD4478_DB5)				            
#define LCD4478_DB6_1	LCD4478_SETBIT(LCD4478_PORT, LCD4478_DB6)				             
#define LCD4478_DB6_0	LCD4478_CLRBIT(LCD4478_PORT, LCD4478_DB6)				             
#define LCD4478_DB7_1	LCD4478_SETBIT(LCD4478_PORT, LCD4478_DB7)				             
#define LCD4478_DB7_0	LCD4478_CLRBIT(LCD4478_PORT, LCD4478_DB7)				            
//------------------------------------------------------------------------------------

//--------------------------------/ Инструкции /--------------------------------------
#define LCD4478_InitPinMode       LCD4478_DDR = 0xFF         // Инициализация на вывод
#define LCD4478_CLEARDISPLAY      0x01                               // Очистка экрана
#define LCD4478_RETURNHOME        0x02         // Вернуться в исходное положение(0x00)
#define LCD4478_ENTRYMODESET      0x04                              // Установить вход
#define LCD4478_DISPLAYCONTROL    0x08                           // Установить дисплей
#define LCD4478_CURSORSHIFT       0x10                                             
#define LCD4478_FUNCTIONSET       0x20                           // Установить функцию
#define LCD4478_SETCGRAM          0x40                                           
#define LCD4478_SETDDRAM          0x80                                          
//------------------------------------------------------------------------------------

//--------------------------- Флаги для DISPLAYCONTROL -------------------------------
#define LCD4478_DISPLAYON         0x04                             // Включить дисплей
#define LCD4478_DISPLAYOFF        0x00                            // Выключить дисплей
#define LCD4478_CURSORON          0x02                              // Включить курсор
#define LCD4478_CURSOROFF         0x00                             // Выключить курсор
#define LCD4478_BLINKON           0x01                    // Мерцающий курсор включить
#define LCD4478_BLINKOFF          0x00                   // Мерцающий курсор выключить
//------------------------------------------------------------------------------------

//--------------------------- Флаги для ENTRYMODESET ---------------------------------
#define LCD4478_ENTRYDECREMENT    0x00                          // Декрементация входа
#define LCD4478_ENTRYINCREMENT    0x02                          // Инкрементация входа
#define LCD4478_ENTRYSHIFTLEFT    0x01                        // Изменение входа влево
#define LCD4478_ENTRYSHIFTRIGHT   0x00                       // Изменение входа вправо
//------------------------------------------------------------------------------------

//--------------------------- Флаги для CURSORSHIFT ----------------------------------
#define LCD4478_DISPLAYMOVE       0x08                                             
#define LCD4478_CURSORMOVE        0x00                                              
#define LCD4478_MOVERIGHT         0x04                                           
#define LCD4478_MOVELEFT          0x00                                            
//------------------------------------------------------------------------------------

//--------------------------- Флаги для FUNCTIONSET ----------------------------------
#define LCD4478_4BITMODE          0x03                       // Установка режима 4 бит
#define LCD4478_2x4BITMODE        0x02            // Установить интерфейс длиной 8 бит
#define LCD4478_2LINE             0x08                                   // Две строки
#define LCD4478_1LINE             0x00                                  // Одна строка
#define LCD4478_5x10DOTS          0x04                       // Отображение 5х10 точек
#define LCD4478_5x8DOTS           0x00                        // Отображение 5х8 точек
//------------------------------------------------------------------------------------

//--------------------------- Флаги для SETDDRAM -------------------------------------
#define LCD4478_DDRAM_1LINE       0x00                                             
#define LCD4478_DDRAM_2LINE       0x40                                              
//------------------------------------------------------------------------------------
