/**********************************************************************
* Code : String Functions
* Devices: TMS320F28x
* Author: Rashi Chauhan
**********************************************************************/
#include <GTSI_1Phase1MPPT.h>                        // Main include file
#include <string.h>
#include <stdio.h>
#include <math.h>

void clearString (char* Str)
{
    int a = 0;
    while(Str[a] != '\0')
    {
        Str[a] = ' ';
        a++;
    }
}

void reverseString (char* Str, Uint16 len )
{
    Uint16 i=0;
    Uint16 j,temp;
    j = len - 1;
    while (i<j)
       {
           temp = Str[i];
           Str[i] = Str[j];
           Str[j] = temp;
           i++;
           j--;
       }
}

Uint16 intToStr(Uint16 x, char str[], Uint16 d) // d represents minimum number of digits
{
    Uint16 i = 0;
    while (x)
    {
        str[i] = (x%10) + '0';
        x = x/10;
        i = i + 1;
    }

    // If number of digits required is more, then
    // add 0s at the beginning
    while (i < d)
    {  str[i] = '0';
       i = i + 1;
    }

    reverseString(str, i);
    str[i] = '\0';
    return i;
}

Uint16 int32ToStr(Uint32 x, char str[], Uint16 d) // d represents minimum number of digits
{
    Uint16 i = 0;
    while (x)
    {
        str[i] = (x%10) + '0';
        x = x/10;
        i = i + 1;
    }

    // If number of digits required is more, then
    // add 0s at the beginning
    while (i < d)
    {  str[i] = '0';
       i = i + 1;
    }

    reverseString(str, i);
    str[i] = '\0';
    return i;
}

void int64ToStr(Uint64 x, char str[], Uint16 d) // d represents minimum number of digits
{
    Uint16 i = 0;
    while (x)
    {
        str[i] = (x%10) + '0';
        x = x/10;
        i = i + 1;
    }

    // If number of digits required is more, then
    // add 0s at the beginning
    while (i < d)
    {  str[i] = '0';
       i = i + 1;
    }

    reverseString(str, i);
    str[i] = '\0';
}

void ftoa(float n, char* res, Uint16 afterpoint)
{
    // Check if the number is negative
    bool_t isNegative = false;
    if (n < 0)
    {
        isNegative = true;
        n = -n; // Convert to positive for further processing
    }

    // Extract integer part
    Uint16 ipart = (Uint16)n;

    // Extract floating part
    float fpart = n - (float)ipart;

    // Convert integer part to string
    Uint16 i = intToStr(ipart, res, 1); // Minimum digits before decimal is 1

    // Check for display option after point
    if (afterpoint != 0)
    {
        res[i] = '.'; // Add dot

        // Get the value of fraction part up to the given number
        // of points after the dot. The third parameter is needed
        // to handle cases like 233.007
        fpart = fpart * powf(10, afterpoint);

        intToStr((Uint16)fpart, res + i + 1, afterpoint);
    }

    // Add the negative sign if necessary
    if (isNegative)
    {
        int j=0;

        // Shift the string to make room for the sign
        for (j = i + afterpoint + 1; j >= 1; j--)
        {
            res[j] = res[j - 1];
        }
        res[0] = '-';
    }
}


void f64toa(float n, char *res, Uint16 afterpoint)  // minimum value of afterpoint should be 1
{
    // Extract integer part
    Uint32 ipart = (Uint32) n;

    // Extract floating part
    float fpart = n - (float) ipart;

    // convert integer part to string
    Uint32 i = int32ToStr(ipart, res, 1); // minimum digits before decimal is 1

    // check for display option after point
    if (afterpoint != 0)
    {
        res[i] = '.';  // add dot

        // Get the value of fraction part upto given no.
        // of points after dot. The third parameter is needed
        // to handle cases like 233.007
        fpart = fpart * powf(10, afterpoint);

        int32ToStr((Uint32) fpart, res + i + 1, afterpoint);
    }
}

bool isDigit(char ch){
    if((Uint16)ch >= 48 && (Uint16)ch <= 57)
        return true;
    else
        return false;
}

float atof(const char* str)
{
    float res = 0.0;  // Result variable
    int i = 0;

    // Process the integer part
    while (isDigit(str[i]))
    {
        res = res * 10.0 + (str[i] - '0');
        i++;
    }

    // Process the fractional part
    if (str[i] == '.')
    {
        float factor = 0.1;
        i++;

        while (isDigit(str[i]))
        {
            res += (str[i] - '0') * factor;
            factor /= 10.0;
            i++;
        }
    }

    return res;
}

float minVal(float x, float y){
    if(x > y)
        return y;
    return x;
}
