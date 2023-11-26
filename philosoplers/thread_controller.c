/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_controller.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamarqu <anamarqu@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 16:07:25 by anamarqu          #+#    #+#             */
/*   Updated: 2023/10/06 16:07:26 by anamarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	loop_controller(t_data *data, unsigned int *counter)
{
	unsigned int	i;

	i = 0;
	while (i < data->num_philos)
	{
		if (get_end_flag(*data) != 0)
			return (-1);
		if (data->num_must_eat != -1
			&& get_philo_end_flag(data->philos[i]) == -1)
		{
			if (get_num_eat(data->philos[i])
				>= (unsigned int)data->num_must_eat)
			{
				set_philo_end_flag(&data->philos[i], 0);
				++ *counter;
				if (*counter >= data->num_philos)
				{
					set_end_flag(data, 2);
					return (-1);
				}
			}
		}
		++i;
	}
	return (1);
}

//Hilo controller. Controla si sigue o si para.
//Si la end flag de un philo es 1, es que termina la simulaci�n.
//Si alguno de los filos llega al n�mero de veces que ha de comer,
//pone su flag a 0 y aumenta el contador.
//Cuando todos han terminado de comer, termina el programa
void	*controller(void *_data)
{
	t_data			*data;
	unsigned int	counter;

	data = (t_data *)_data;
	counter = 0;
	while (1)
	{
		if (loop_controller(data, &counter) == -1)
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}
