/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 19:10:05 by mg                #+#    #+#             */
/*   Updated: 2024/11/25 10:26:25 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	ft_print_adresse(void *ptr)
{
	unsigned long	adresse;
	int				count;

	adresse = (unsigned long)ptr;
	count = 0;
	count += ft_putstr_opti("0x");
	count += ft_print_hex_min(adresse);
	return (count);
}

int	ft_print_hex_min(unsigned long num)
{
	int		count;
	char	*hex_digits;

	count = 0;
	hex_digits = "0123456789abcdef";
	if (num >= 16)
		count += ft_print_hex_min(num / 16);
	count += ft_putchar(hex_digits[num % 16]);
	return (count);
}

int	ft_print_hex_maj(unsigned long num)
{
	int		count;
	char	*hex_digits;

	count = 0;
	hex_digits = "0123456789ABCDEF";
	if (num >= 16)
		count += ft_print_hex_maj(num / 16);
	count += ft_putchar(hex_digits[num % 16]);
	return (count);
}
