/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gribeiro <gribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:09:40 by ruida-si          #+#    #+#             */
/*   Updated: 2025/04/03 17:40:38 by gribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "minishell.h"

int	ft_putchar(int c);
int	ft_putstr(char *str);
int	ft_putnbr(long n, int base, int count, int cap);

int	pf_print(va_list *ap, char spec, int count)
{
	if (spec == 'c')
		count = ft_putchar(va_arg(*ap, int));
	else if (spec == '%')
		count = ft_putchar('%');
	else if (spec == 's')
		count = ft_putstr(va_arg(*ap, char *));
	else if (spec == 'i' || spec == 'd')
		count = ft_putnbr(va_arg(*ap, int), 10, 0, 0);
	else if (spec == 'u')
		count = ft_putnbr(va_arg(*ap, unsigned int), 10, 0, 0);
	else if (spec == 'x')
		count = ft_putnbr(va_arg(*ap, unsigned int), 16, 0, 0);
	else if (spec == 'X')
		count = ft_putnbr(va_arg(*ap, unsigned int), 16, 0, -32);	
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		count;
	int		i;
	
	i = 0;
	count = 0;
	if (!format)
		return (-1);
	va_start(ap, format);
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1])
		{
			count += pf_print(&ap, format[++i], 0);
		}
		else
			count += ft_putchar(format[i]);
		i++;
	}
	va_end(ap);
	return (count);
}

int	ft_putchar(int c)
{
	return (write(2, &c, 1));
}

int	ft_putstr(char *str)
{
	int	i;

	i = 0;
	if (!str)
		str = "(null)";
	while (*str)
	{
		write(2, str, 1);
		str++;
		i++;
	}
	return (i);
}

int	ft_putnbr(long n, int base, int count, int cap)
{
	char	*hexa;

	hexa = "0123456789abcdef";
	if (n < 0)
	{
		count += ft_putchar('-');
		n = -n;
	}
	if (n < base)
	{
		if (n > 9)
			count += ft_putchar(hexa[n] + cap);
		else
			count += ft_putchar(hexa[n]);
	}
	else
	{
		count += ft_putnbr(n / base, base, 0, cap);
		count += ft_putnbr(n % base, base, 0, cap);
	}
	return (count);
}
