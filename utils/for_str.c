/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_str.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 11:10:15 by mg                #+#    #+#             */
/*   Updated: 2024/11/21 11:16:23 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_strlen(char *str)
{
	int i;

	i = 0;
	while (*str)
		i++;
	return (i);
}