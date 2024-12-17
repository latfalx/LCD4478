#ifndef _LCD4478_INSTRUCTION_H_
#define _LCD4478_INSTRUCTION_H_
/** Описание команд для дисплея без префикса \c LCD4478:
 * \author latfalx \date 23.11.2024
 *  * MODE_4BIT - Режим работы по 4 битам.
 *  * MODE_TWICE_4BIT - Режим отправки байта, дважды по 4 бита.
 *  * FUNCTION_SET - Установка функций для дисплея.
 *      | FUNCTION_8BIT - Передача данных по 8 битам.
 *      | FUNCTION_4BIT - Передача данных по 4 битам.
 *      | FUNCTION_1LINE - Одна строка.
 *      | FUNCTION_2LINE - Две строки.
 *      | FUNCTION_5x8DOTS - Отображение 5х8 точек.
 *      | FUNCTION_5x10DOTS - Отображение 5х10 точек.
 *      \example (LCD4478_FUNCTION_SET | LCD4478_FUNCTION_4BIT | LCD4478_FUNCTION_2LINE | LCD4478_FUNCTION_5x8DOTS)
 *  * DISPLAY_SET - Устанавливает отображения дисплея.
 *      | DISPLAY_ON - Включить дисплей.
 *      | DISPLAY_OFF - Выключить дисплей.
 *      | DISPLAY_CURSOR_ON - Включить курсор.
 *      | DISPLAY_CURSOR_OFF - Выключить курсор.
 *      | DISPLAY_BLINK_ON - Включить мигающий символ (курсор).
 *      | DISPLAY_BLINK_OFF - Выключить мигающий символ (курсор).
 *      \example (LCD4478_DISPLAY_SET | LCD4478_DISPLAY_OFF)
 *  * DISPLAY_CLEAR - Очищает весь дисплей и устанавливает адрес DDRAM в 0.
 *  * ENTRY_SET - Устанавливает направление перемещения курсора и задает сдвиг дисплея во время записи и чтения данных.
 *      | ENTRY_INCREMENT - Увеличивать направление перемещение курсора.
 *      | ENTRY_DECREMENT - Уменьшать направление перемещение курсора.
 *      | ENTRY_SHIFT_DISPLAY_ON - Включить сдвиг дисплея во время записи и чтения данных.
 *      | ENTRY_SHIFT_DISPLAY_OFF - Выключить сдвиг дисплея во время записи и чтения данных.
 *  * MOVE_SET - Установить перемещение курсора и сдвинуть отображение без изменения содержимого DDRAM.
 *      | MOVE_DISPLAY - Сдвинуть отображение без изменения содержимого DDRAM.
 *      | MOVE_CURSOR - Перемещение курсора.
 *      | MOVE_RIGHT - Сдвинуть вправо.
 *      | MOVE_LIFT - Сдвинуть влево.
 *  * MOVE_HOME - Устанавливает адрес DDRAM в 0. Также возвращает исходное отображение. Содержимое DDRAM остается неизменным.
 *  * DDRAM_SET - Устанавливает адрес DDRAM. После этой настройки данные DDRAM отправляются и принимаются.
 *      | DDRAM_1LINE - Адрес 1 строки для установки.
 *      | DDRAM_2LINE - Адрес 2 строки для установки.
 *  * CGRAM_SET - Устанавливает адрес CGRAM. Данные CGRAM отправляются и принимаются после этой настройки.
 */

/*  Режим работы по 4 битам.    */
#define LCD4478_MODE_4BIT               0x03
/*  Режим отправки байта, дважды по 4 бита. */
#define LCD4478_MODE_TWICE_4BIT         0x02

/*  Установка функций для дисплея.  */
#define LCD4478_FUNCTION_SET            0x20
/*  Передача данных по 8 битам. */
#define LCD4478_FUNCTION_8BIT           0x10 
/*  Передача данных по 4 битам. */
#define LCD4478_FUNCTION_4BIT           0x00
/*  Одна строка.    */
#define LCD4478_FUNCTION_1LINE          0x00
/*  Две строки. */
#define LCD4478_FUNCTION_2LINE          0x08
/*  Отображение 5х8 точек.  */
#define LCD4478_FUNCTION_5x8DOTS        0x00
/*  Отображение 5х10 точек.  */
#define LCD4478_FUNCTION_5x10DOTS       0x04

/*  Устанавливает отображения дисплея.  */
#define LCD4478_DISPLAY_SET             0x08
/*  Включить дисплей.   */
#define LCD4478_DISPLAY_ON              0x04
/*  Выключить дисплей.  */
#define LCD4478_DISPLAY_OFF             0x00
/*  Включить курсор.    */
#define LCD4478_DISPLAY_CURSOR_ON       0x02
/*  Выключить курсор.   */
#define LCD4478_DISPLAY_CURSOR_OFF      0x00
/*  Включить мигающий символ (курсор).  */
#define LCD4478_DISPLAY_BLINK_ON        0x01
/*  Выключить мигающий символ (курсор). */
#define LCD4478_DISPLAY_BLINK_OFF       0x00

/*  Очищает весь дисплей и устанавливает адрес DDRAM в 0.   */
#define LCD4478_DISPLAY_CLEAR           0x01

/*  Устанавливает направление перемещения курсора и 
задает сдвиг дисплея во время записи и чтения данных.   */
#define LCD4478_ENTRY_SET               0x04
/*  Увеличивать направление перемещение курсора.    */
#define LCD4478_ENTRY_INCREMENT         0x02
/*  Уменьшать направление перемещение курсора.  */
#define LCD4478_ENTRY_DECREMENT         0x00
/*  Включить сдвиг дисплея во время записи и чтения данных. */
#define LCD4478_ENTRY_SHIFT_DISPLAY_ON  0x01
/*  Выключить сдвиг дисплея во время записи и чтения данных.    */
#define LCD4478_ENTRY_SHIFT_DISPLAY_OFF 0x00

/*  Установить перемещение курсора и сдвинуть отображение без изменения содержимого DDRAM.  */
#define LCD4478_MOVE_SET                0x10
/*  Сдвинуть отображение без изменения содержимого DDRAM.   */
#define LCD4478_MOVE_DISPLAY            0x08
/*  Перемещение курсора.    */
#define LCD4478_MOVE_CURSOR             0x00
/*  Сдвинуть вправо.    */
#define LCD4478_MOVE_RIGHT              0x04
/*  Сдвинуть влево. */
#define LCD4478_MOVE_LIFT               0x00

/*  Устанавливает адрес DDRAM в 0. Также возвращает исходное отображение. Содержимое DDRAM остается неизменным. */
#define LCD4478_MOVE_HOME               0x02

/*  Устанавливает адрес DDRAM. После этой настройки данные DDRAM отправляются и принимаются.    */
#define LCD4478_DDRAM_SET               0x80
/*  Адрес 1 строки для установки.   */
#define LCD4478_DDRAM_1LINE             0x00
/*  Адрес 2 строки для установки.   */
#define LCD4478_DDRAM_2LINE             0x40

/*  Устанавливает адрес CGRAM. Данные CGRAM отправляются и принимаются после этой настройки.    */
#define LCD4478_CGRAM_SET               0x40
#endif /* _LCD4478_INSTRUCTION_H_ */ 