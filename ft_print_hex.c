/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suobeida <suobeida@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/18 16:15:02 by suobeida          #+#    #+#             */
/*   Updated: 2026/10/18 17:13:42 by suobeida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_puthex(unsigned int n, int upper)
{
	char	*base;
	int		count;
	int		ret;

	if (upper)
		base = "0123456789ABCDEF";
	else
		base = "0123456789abcdef";
	count = 0;
	if (n >= 16)
	{
		ret = ft_puthex(n / 16, upper);
		if (ret < 0)
			return (-1);
		count += ret;
	}
	write(1, &base[n % 16], 1);
	return (count + 1);
}
