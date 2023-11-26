/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamarqu <anamarqu@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 11:47:14 by anamarqu          #+#    #+#             */
/*   Updated: 2023/10/06 11:47:16 by anamarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philosophers.h"

void	destroy_mutex(t_data *data)
{
	unsigned int	i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_destroy(&data->philos[i].time_last_mutex);
		usleep(10);
		pthread_mutex_destroy(&data->philos[i].num_bites_mutex);
		usleep(10);
		pthread_mutex_destroy(&data->philos[i].end_flag_mutex);
		usleep(10);
		pthread_mutex_destroy(&data->forks[i].fork_mutex);
		++i;
	}
	usleep(100);
	pthread_mutex_destroy(&data->end_flag_mutex);
	usleep(100);
	pthread_mutex_destroy(&data->print_mutex);
}

int	create_threads(t_data *data)
{
	unsigned int	i;

	i = 0;
	if (pthread_create(&data->thread_controller,
			NULL, &controller, data) != 0)
	{
		perror("phtread_create");
		return (-1);
	}
	while (i < data->num_philos)
	{
		if (pthread_create(&data->philos[i].thread, NULL,
				&thread_philo_routine, &data->philos[i]) != 0)
		{
			perror("phtread_create");
			return (-1);
		}
		++i;
	}
	return (1);
}

int	special_cases(t_data *data)
{
	if (data->time_to_die == 0)
	{
		printf("%s0 1 DIED\n", RED);
		return (0);
	}
	if (data->num_must_eat == 0)
		return (0);
	return (1);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	if ((argc < 5) || (argc > 6))
	{
		printf("Error! Numero erroneo de argumentos\n");
		return (-1);
	}
	if (check_input(argc, argv) == 0)
		return (-1);
	init_data(argc, argv, &data);
	data.time_start = get_time_in_ms();
	if (special_cases(&data) == 0)
		return (0);
	if (create_threads(&data) == -1)
		return (-1);
	if (join_threads(&data) == -1)
		return (-1);
	destroy_mutex(&data);
	return (0);
}
