
#include"helper.h"

int helper::GetLength(const char array[])
{
	int count = 0;
	for (int i = 0; array[i] != '\0'; i++)
	{
		count++;
	}
	return count;
}

void helper::copyString( char str1[], const char str2[], int len)
{
	int i = 0;
	while (str2[i] != '\0')
	{
		str1[i] = str2[i];
		i++;
	}
	str1[i] = '\0';
}

void helper::Namer(char str1[], char str2[], char str3[])
{
	int i = 0;
	int k = 0;
	while (str2[i] != '\0')
	{
		str1[k++] = str2[i];
		i++;
	}
	str1[k++] = ' ';
	i = 0;
	while (str3[i] != '\0')
	{
		str1[k++] = str3[i];
		i++;
	}
	str1[k] = '\0';


}

bool helper::compareStrings(const char* str1, const char* str2)
{
	
	if (str1 != nullptr && str2 != nullptr)
	{
		while (*str1 && *str2) {

			if (*str1 != *str2) {
				return false;
			}

			++str1;
			++str2;
		}

		return *str1 == '\0' && *str2 == '\0';
	}
	else {
		return false;
	}
	
}