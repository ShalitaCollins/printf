#include "main.h"

/**
* _print - function that gives output depending to a format
* @format: format depending to the printed argument 
* Return: return numbers of printed  char
*/

int _printf(const char *format, ...)
{

         int count = 0;
        va_list args;

       if (format == NULL)
                    return (-1);

        va_start(args, format);

       while (*format)
      {
               if (*format != '%')
              {     
               
                           write(1, format, 1);
               }

               format++; 
      }

      return (count);
}            
