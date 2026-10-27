/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suobeida <suobeida@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/18 16:08:47 by suobeida          #+#    #+#             */
/*   Updated: 2026/10/18 17:15:54 by suobeida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>

static int	ft_puthexa(unsigned long n)
{
	char	*base;
	int		count;

	base = "0123456789abcdef";
	count = 0;
	if (n >= 16)
		count += ft_puthexa(n / 16);
	write(1, &base[n % 16], 1);
	return (count + 1);
}

int	ft_putptr(void *ptr)
{
	unsigned long	address;
	int				count;

	if (!ptr)
		return (write(1, "(nil)", 5));
	address = (unsigned long)ptr;
	count = 0;
	count += write(1, "0x", 2);
	count += ft_puthexa(address);
	return (count);
}
