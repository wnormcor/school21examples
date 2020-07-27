#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>

int g_result;
int g_width;
int g_dot;

static void ft_putchar(char c)
{
    write(1, &c, 1);
    g_result += 1;
}

static void ft_putstr(char *str, int len)
{
    while (*str != '\0' && len > 0)
    {
        ft_putchar(*str);
        str++;
        len--;
    }
}

static int ft_strlen(char *str)
{
    int len = 0;
    while (*str++ != '\0')
        len++;
    return (len);
}

static char *ft_itoa(unsigned long nbr, int base)
{
    unsigned long temp_nbr = nbr;
    int len = 0;
    char *str = NULL;
    if (nbr == 0)
        len++;
    while (temp_nbr > 0)
    {
        temp_nbr /= base;
        len++;
    }
    str = malloc(len + 1);
    str[len] = '\0';
    while (len > 0)
    {
        str[len - 1] = nbr % base;
        if (nbr % base > 9)
            str[len - 1] += 'a' - 10;
        else
            str[len - 1] += '0';
        nbr /= base;
        len--;
    }
    return (str);
}

static void ft_printf_x(unsigned long nbr)
{
    char *str;
    str = ft_itoa(nbr, 16);
    int len = ft_strlen(str);

    if (g_dot != -1 && g_dot > len)
        len = g_dot;
    while (g_width > len)
        { ft_putchar(' '); g_width--; }
    while (len > ft_strlen(str))
        { ft_putchar('0'); len--; }
    ft_putstr(str, ft_strlen(str));
    free(str);
}

static void ft_printf_d(long nbr)
{
    char *str;
    int minus = 0;
    if (nbr < 0)
        { minus = 1; nbr *= -1; }
    str = ft_itoa(nbr, 10);
    int len = ft_strlen(str);

    if (g_dot != -1 && g_dot > len)
        len = g_dot;
    if (minus == 1 && g_width > 0)
        { g_width--; }
    while (g_width > len)
        { ft_putchar(' '); g_width--; }
    if (minus == 1)
        { ft_putchar('-'); }
    while (len > ft_strlen(str))
        { ft_putchar('0'); len--; }
    ft_putstr(str, ft_strlen(str));
    free(str);
}

static void ft_printf_s(char *str)
{
    int len = ft_strlen(str);

    if (g_dot != -1 && g_dot < len)
        len = g_dot;
    while (g_width > len)
        { ft_putchar(' '); g_width--; }
    ft_putstr(str, len);
}

int ft_printf(const char *str, ... )
{
    g_result = 0;
    int i = 0;
    va_list ap;

    va_start(ap, str);
    while (str[i] != '\0')
    {
        if (str[i] == '%' && str[i+1] != '\0')
        {
            i++;
            g_width = 0;
            g_dot = -1;
            while (str[i] >= '0' && str[i] <= '9')
            {
                g_width = g_width * 10 + (str[i] - '0');
                i++;
            }
            if (str[i] == '.')
            {
                g_dot = 0;
                i++;
                while (str[i] >= '0' && str[i] <= '9')
                {
                    g_dot = g_dot * 10 + (str[i] - '0');
                    i++;
                }
            }
            if (str[i] == 's')
                ft_printf_s(va_arg(ap, char *));
            else if (str[i] == 'x')
                ft_printf_x(va_arg(ap, unsigned int));
            else if (str[i] == 'd')
                ft_printf_d(va_arg(ap, int));
            else
                ft_putchar(str[i]);
        }
        else
            ft_putchar(str[i]);
        i++;
        
    }
    va_end(ap);
    return (g_result);
}

/* delete befor upload */

#include <stdio.h>

int main(void)
{
    printf("[%10.2s]\n", "toto");
    ft_printf("[%10.2s]\n", "toto");
    printf("Magic [%s] is [%10.5d]\n", "number", -42);
    ft_printf("Magic [%s] is [%10.5d]\n", "number", -42);
    printf("Hexadecimal for [%.5d] is [%10.5x]\n", -42, 42);
    ft_printf("Hexadecimal for [%.5d] is [%10.5x]\n", -42, 42);
}