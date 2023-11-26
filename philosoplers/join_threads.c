/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamarqu <anamarqu@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 16:07:25 by anamarqu          #+#    #+#             */
/*   Updated: 2023/10/06 16:07:26 by anamarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philosophers.h"

int	join_controller(t_data *data)
{
	usleep(100);
	if (pthread_join(data->thread_controller, NULL) != 0)
	{
		perror("pthread_join");
		return (-1);
	}
	usleep(100);
	return (1);
}

int	join_threads(t_data *data)
{
	unsigned int	i;

	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_join(data->philos[i].thread, NULL) != 0)
		{
			perror("pthread_join");
			return (-1);
		}
		usleep(100);
		++i;
	}
	if (join_controller(data) == -1)
		return (-1);
	return (1);
}
