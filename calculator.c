/*#include"lcd .h"
#include"kpm.h"
#include"types.h"
#include"delay.h"

u32 readnum(void)
{
        u32 sum=0,num=0;
        while(1)
        {
                num=key_scan(); // Wait for a keypress
                delay_ms(100);
                if((num >='0') && (num <='9'))  //If key is digit
                {
                        sum=(sum*10)+(num-'0');
                        Charlcd(num); // Display digit on LCD
                        while(colscan()==0);// Wait until key is released
                }
                else if(num=='#')
                {
                        while(colscan()==0);
                        break;
                }
        }
        return sum;
}
int main()
{
        s32 val1,val2,res;
        u8 choice;
        Initlcd();
        initkpm();
        Strlcd("Calculator:");
        while(1)
        {
                Cmdlcd(0xc0);
                val1=readnum();
                delay_ms(100);
                choice=key_scan();
                delay_ms(100);
                while(colscan()==0);
                Charlcd(choice);
                val2=readnum();
                delay_ms(100);
                switch(choice)
                {
                        case '+':res=val1+val2;
                                        break;
                        case '-':res=val1-val2;
                                        break;
                        case '*':res=val1*val2;
                                        break;
                        case '/':res=val1/val2;
                                        break;
                }
                choice=key_scan();
                delay_ms(100);
                while(colscan()==0);
                if(choice=='=')
                {
                        Charlcd(choice);
                        S32lcd(res);
                        delay_ms(500);
                        choice=key_scan();
                        delay_ms(100);
                        while(colscan()==0);
                        if(choice=='=')
                        {
                                         Cmdlcd(0xc0);
                                         Strlcd("              ");
                        }
                }
        }
}
*/
/*
#include "lcd .h"
#include "kpm.h"
#include "types.h"
#include "delay.h"

int main()
{
    s32 num1 = 0, num2 = 0, result = 0;
    u8 key, op;

    Initlcd();         // LCD init
    initkpm();         // Keypad init
    Strlcd("Calculator:");

    while (1)
    {
        // Reset for new calculation
        num1 = num2 = result = 0;
        op = 0;
        Cmdlcd(0xC0); // Move to second line

        // --- First number ---
        while (1)
        {
            key = key_scan();
            delay_ms(100);
            while (colscan() == 0);

            if (key >= '0' && key <= '9')
            {
                Charlcd(key);
                num1 = num1 * 10 + (key - '0');
            }
            else if (key == '+' || key == '-' || key == '*' || key == '/')
            {
                op = key;
                Charlcd(op);
                break;
            }
        }

        // --- Second number ---
        while (1)
        {
            key = key_scan();
            delay_ms(100);
            while (colscan() == 0);

            if (key >= '0' && key <= '9')
            {
                Charlcd(key);
                num2 = num2 * 10 + (key - '0');
            }
            else if (key == '=')
            {
                Charlcd('=');
                switch (op)
                {
                    case '+': result = num1 + num2; break;
                    case '-': result = num1 - num2; break;
                    case '*': result = num1 * num2; break;
                    case '/': result = (num2 != 0) ? num1 / num2 : 0; break;
                }
                S32lcd(result);
                delay_ms(2000);
                break;
            }
						
        }
    }
}
*/

#include "lcd .h"
#include "kpm.h"
#include "types.h"
#include "delay.h"

int main()
{
    s32 num1 = 0, num2 = 0, result = 0;
    u8 key, op;
    u8 digit_count = 0;  // For tracking digits entered

    Initlcd();         // LCD init
    initkpm();         // Keypad init
    Strlcd("Calculator:");

    while (1)
    {
        num1 = num2 = result = 0;
        op = 0;
        Cmdlcd(0xC0); // Move to second line

        // --- First number ---
        digit_count = 0;
        while (1)
        {
            key = key_scan();
            delay_ms(100);
            while (colscan() == 0);

            if (key >= '0' && key <= '9')
            {
                Charlcd(key);
                num1 = num1 * 10 + (key - '0');
                digit_count++;
            }
            else if (key == 'B') // Backspace key
            {
                if (digit_count > 0)
                {
                    num1 /= 10;  // Remove last digit
                    digit_count--;
                    Cmdlcd(0x10); // Move cursor left
                    Charlcd(' '); // Erase last char
                    Cmdlcd(0x10); // Move cursor left again
                }
            }
            else if (key == '+' || key == '-' || key == '*' || key == '/')
            {
                op = key;
                Charlcd(op);
                break;
            }
        }

        // --- Second number ---
        digit_count = 0;
        while (1)
        {
            key = key_scan();
            delay_ms(100);
            while (colscan() == 0);

            if (key >= '0' && key <= '9')
            {
                Charlcd(key);
                num2 = num2 * 10 + (key - '0');
                digit_count++;
            }
            else if (key == 'B') // Backspace key
            {
                if (digit_count > 0)
                {
                    num2 /= 10;  // Remove last digit
                    digit_count--;
                    Cmdlcd(0x10); // Move cursor left
                    Charlcd(' '); // Erase last char
                    Cmdlcd(0x10); // Move cursor left again
                }
            }
            else if (key == '=')
            {
                Charlcd('=');
                switch (op)
                {
                    case '+': result = num1 + num2; break;
                    case '-': result = num1 - num2; break;
                    case '*': result = num1 * num2; break;
                    case '/': result = (num2 != 0) ? num1 / num2 : 0; break;
                }
                S32lcd(result);
                delay_ms(2000);
                break;
            }
        }
    }
}
