#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<ctype.h>

int main(void)
{
	int8_t input[20]={66,114,117,99,101,32,83,97,121,115,32,72,105,33,7,9,50,\
		48,49,57};
	char *type = NULL;
	for (int i = 0; i < 20; i++)
	{
		if(islower((char) input[i]))
		{
			type = "Lower Case";	
		}
		else if(isupper((char) input[i]))
		{
			type = "Upper Case";
		}
		else if((input[i] >= 0 && input[i] <= 32) || input[i] == 127)
		{
			type = "White Space";
		}
		else if((input[i] >= 33 && input[i] <= 47) \
		     || (input[i] >= 58 && input[i] <= 64) \
		     || (input[i] >= 91 && input[i] <= 96) \
		     || (input[i] >= 123 && input[i] <= 126))
		{
			type = "Special Character";
		}
		else if(isdigit((char) input[i]))
		{
			type = "Digit";
		}
		printf("Code: %-6d\tType: %-20s\tASCII Char: %-5c\n", input[i], \
				type, (char)input[i]);
	}
	return 0;
}
