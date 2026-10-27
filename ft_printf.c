/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suobeida <suobeida@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/10 15:29:24 by suobeida          #+#    #+#             */
/*   Updated: 2026/10/18 17:34:28 by suobeida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_convert(char spec, va_list *args)
{
	if (spec == 'c')
		return (ft_putchar((char)va_arg(*args, int)));
	else if (spec == 's')
		return (ft_putstr(va_arg(*args, char *)));
	else if (spec == 'p')
		return (ft_putptr(va_arg(*args, void *)));
	else if (spec == 'd' || spec == 'i')
		return (ft_putnbr(va_arg(*args, int)));
	else if (spec == 'u')
		return (ft_putunbr(va_arg(*args, unsigned int)));
	else if (spec == 'x')
		return (ft_puthex(va_arg(*args, unsigned int), 0));
	else if (spec == 'X')
		return (ft_puthex(va_arg(*args, unsigned int), 1));
	else if (spec == '%')
		return (ft_putchar('%'));
	return (-1);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		i;
	int		count;

	if (!format)
		return (-1);
	i = 0;
	count = 0;
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1])
		{
			i++;
			count += ft_convert(format[i], &args);
		}
		else
			count += ft_putchar(format[i]);
		i++;
	}
	va_end(args);
	return (count);
}
