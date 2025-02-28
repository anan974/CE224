#include "Oled.h"


void oled_cmd_1byte(I2C_TypeDef *I2Cx, char data)
{
    i2c_start(I2Cx);
    i2c_add(I2Cx, 0x78, 0);
    i2c_data(I2Cx, 0x00);  
    i2c_data(I2Cx, data);  
    i2c_stop(I2Cx);
}



void oled_cmd_2byte(I2C_TypeDef *I2Cx, char data[])
{
    i2c_start(I2Cx);
    i2c_add(I2Cx, 0x78, 0);
    i2c_data(I2Cx, 0x00);  
    i2c_data(I2Cx, data[0]);
    i2c_data(I2Cx, data[1]);
    i2c_stop(I2Cx);
}


void oled_init(I2C_TypeDef *I2Cx, char screen_size)
{
    i2c_init(I2Cx, i2c_FM);

    // Send init command to the OLED
    char cmd[] = {0xA8, 0x3F};
    oled_cmd_2byte(I2Cx, cmd);
    
    char cmd1[] = {0xD3, 0x00};
    oled_cmd_2byte(I2Cx, cmd1);
    
    oled_cmd_1byte(I2Cx, 0x40);
    oled_cmd_1byte(I2Cx, 0xA1);
    oled_cmd_1byte(I2Cx, 0xC8);
    
    char cmd2[] = {0xDA, screen_size};
    oled_cmd_2byte(I2Cx, cmd2);
    
    char cmd3[] = {0x81, 0x7F};
    oled_cmd_2byte(I2Cx, cmd3);
    
    oled_cmd_1byte(I2Cx, 0xA4);
    oled_cmd_1byte(I2Cx, 0xA6);
    
    char cmd4[] = {0xD5, 0x80};
    oled_cmd_2byte(I2Cx, cmd4);
    
    char cmd5[] = {0x8D, 0x14};
    oled_cmd_2byte(I2Cx, cmd5);
    
    oled_cmd_1byte(I2Cx, 0xAF);
    
    char cmd6[] = {0x20, 0x10};
    oled_cmd_2byte(I2Cx, cmd6);
}

void oled_init_64(I2C_TypeDef *I2Cx)
{
    // Initialize OLED 64
    oled_init(I2Cx, 0x12);
		
		oled_clear(I2C1);
		oled_print(I2C1,3,30,"Init done ", 's');
}


void oled_data(I2C_TypeDef *I2Cx, char data)
{
    i2c_start(I2Cx);
    i2c_add(I2Cx, 0x78, 0);
    i2c_data(I2Cx, 0x40);  
    i2c_data(I2Cx, data);  
    i2c_stop(I2Cx);
}



void oled_pos(I2C_TypeDef *I2Cx, char Ypos, char Xpos)
{
    oled_cmd_1byte(I2Cx, 0x00 + (0x0F & Xpos));
    oled_cmd_1byte(I2Cx, 0x10 + (0x0F & (Xpos >> 4)));
    oled_cmd_1byte(I2Cx, 0xB0 + Ypos);
}


void oled_clear(I2C_TypeDef *I2Cx)
{
    int i, j;
    oled_pos(I2Cx, 0, 0);
    for (i = 0; i < 8; i++)
    {
        for (j = 0; j < 128; j++)
        {
            oled_data(I2Cx, 0x00); 
        }
    }
    oled_pos(I2Cx, 0, 0);
}

void oled_msg(I2C_TypeDef *I2Cx, char str[]) {
    int i, j;
    i = 0;
    while (str[i]) {
        for (j = 0; j < 5; j++) {
            oled_data(I2Cx, ASCII[(str[i] - 32)][j]);
        }
        i++;
    }
}

void oled_print(I2C_TypeDef *I2Cx, char Ypos, char Xpos, void* data, char type) {
    char buffer[100];
		int i = 0;
    if (type == 'i') {  //int
        int_to_string(*(int*)data, buffer);
    } 
    else if (type == 'd') {  //  double
        double_to_string(*(double*)data, buffer, 2);  
    } 
    else if (type == 's') 
		{  //  string
       char* str = (char*)data;
        while (str[i] != '\0') {
            buffer[i] = str[i];
            i++;
        }
        buffer[i] = '\0';  
    }
    oled_pos(I2Cx, Ypos, Xpos);
    oled_msg(I2Cx, buffer);
}

//// Convert other data type to string on oled


void int_to_string(int num, char* str) {
    int i = 0;
    int is_negative = 0;
    if (num == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return;
    }
    if (num < 0) {
        is_negative = 1;
        num = -num;
    }
    
    // Ð?o ngu?c chu?i
    while (num > 0) {
        str[i++] = (num % 10) + '0';
        num /= 10;
    }
    
    if (is_negative) {
        str[i++] = '-';
    }

    // Ð?o ngu?c chu?i d? có d?ng chính xác
    str[i] = '\0';
    int start = 0;
    int end = i - 1;
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

void double_to_string(double num, char* str, int decimal_places) {
    int int_part = (int)num;
    double dec_part = num - int_part;
    int_to_string(int_part, str);
    
    int len = 0;
    while (str[len] != '\0') len++; // Tìm d? dài c?a ph?n nguyên
    
    if (decimal_places > 0) {
        str[len++] = '.';  // Thêm d?u ch?m cho ph?n th?p phân
        for (int i = 0; i < decimal_places; i++) {
            dec_part *= 10;
            int digit = (int)dec_part;
            str[len++] = (char)(digit + '0');
            dec_part -= digit;
        }
    }
    str[len] = '\0';
}
