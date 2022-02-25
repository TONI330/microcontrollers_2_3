/*
 * lcd.h
 *
 * Created: 23/02/2022 13:34:30
 *  Author: tjtle
 */ 


#ifndef LCD_H_
#define LCD_H_


void init(void);
void display_text(char *str);
void set_cursor(int position);


#endif /* LCD_H_ */