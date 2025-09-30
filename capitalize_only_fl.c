#include "lcd .h"
#include "lcd_defines.h"
#include "types.h"
#include "delay.h"
#include <lpc21xx.h>
#include <string.h>
#include <ctype.h>

#define SW1 1 // P0.1
#define SW2 2 // P0.2

void capitalize_words(char *str);

char str1[32] = "vector india";
char str2[32] = "vector hyderabad";
char temp[32];

int main() 
{
	Initlcd();
	while (1) {
	if (((IOPIN0 >> SW1) & 1) == 0) 
	{
	Cmdlcd(CLEAR_LCD);
	strcpy(temp, str1);
	Cmdlcd(GOTO_LINE1_POS0);
	Strlcd(temp);


	while (((IOPIN0 >> SW1) & 1) == 0);

	capitalize_words(temp);
	Cmdlcd(GOTO_LINE2_POS0);
	Strlcd(temp);
	delay_ms(2000);
	}
else if (((IOPIN0 >> SW2) & 1) == 0) 
	{
	Cmdlcd(CLEAR_LCD);
	strcpy(temp, str2);
	Cmdlcd(GOTO_LINE1_POS0);
	Strlcd(temp); // Display original string

	// Wait for switch release
	while (((IOPIN0 >> SW2) & 1) == 0);

	capitalize_words(temp);
	Cmdlcd(GOTO_LINE2_POS0);
	Strlcd(temp); // Display capitalized string
				//capitalize_words(temp);
	delay_ms(2000);
	}

// No switch is pressed
	else
		{
				Cmdlcd(GOTO_LINE1_POS0);
				Strlcd("Waiting input    ");
				Cmdlcd(GOTO_LINE2_POS0);
				Strlcd("                  ");
}
}
}


void capitalize_words(char *str) {
int i = 0;
int capitalize_next = 1;

while (str[i] != '\0')
 {
		if (str[i] == ' ')
		{
			capitalize_next = 1;
		}
		else if (capitalize_next && str[i] >= 'a' && str[i] <= 'z')
		{
				str[i] = str[i] - 32; // Convert to uppercase
				capitalize_next = 0;
		}
		else
		{
		capitalize_next = 0;
		}
i++;
}
}

