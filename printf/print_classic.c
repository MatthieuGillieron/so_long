/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_print1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 19:00:42 by mg                #+#    #+#             */
/*   Updated: 2024/11/21 11:03:00 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_char(int c)
{
	ft_putchar(c);
	return (1);
}

int	ft_print_str(char *str)
{
	int	len;

	if (!str)
	{
		write(1, "(null)", 6);
		return (6);
	}
	len = 0;
	while (str[len])
		len++;
	write(1, str, len);
	return (len);
}

int	ft_print_digit(int nb)
{
	int	count;

	count = 0;
	if (nb == -2147483648)
	{
		write(1, "-2147483648", 11);
		return (11);
	}
	if (nb < 0)
	{
		count += ft_putchar('-');
		nb = -nb;
	}
	if (nb > 9)
		count += ft_print_digit(nb / 10);
	count += ft_putchar((nb % 10) + '0');
	return (count);
}

int	ft_print_unsigned(unsigned int nb)
{
	int	count;

	count = 0;
	if (nb > 9)
		count += ft_print_unsigned(nb / 10);
	count += ft_putchar((nb % 10) + '0');
	return (count);
}
