
#ifndef _LCD_H
#define _LCD_H

void lcd_init();
void lcd_print(byte, char*);
void lcd_print_time(byte, rtc_time*);
void lcd_print_date(byte, rtc_time*);

#endif
