/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamarqu <anamarqu@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 11:47:14 by anamarqu          #+#    #+#             */
/*   Updated: 2023/10/06 11:47:16 by anamarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philosophers.h"

int	check_only_numbers(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	atoi_limits(char *str)
{
	unsigned long long int	nb;
	int						i;

	i = 0;
	nb = 0;
	while (str[i] != '\0' && (str[i] >= '0' && str[i] <= '9'))
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	if (nb > INT_MAX)
		return (-1);
	return ((int)nb);
}

int	check_input(int argc, char *argv[])
{
	int	i;
	int	nb;

	i = 1;
	while (i < argc)
	{
		if (check_only_numbers(argv[i]) == 0)
		{
			printf("Error! Solo digitos enteros\n");
			return (0);
		}
		nb = atoi_limits(argv[i]);
		if (i == 1 && (nb <= 0 || nb > 200))
		{
			printf("Error! Numero de filosofos debe estar entre 1 y 200\n");
			return (0);
		}
		if (i != 1 && nb == -1)
		{
			printf("Error! Numero demasiado alto\n");
			return (0);
		}
		i++;
	}
	return (1);
}
