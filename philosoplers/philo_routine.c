/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamarqu <anamarqu@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 11:47:14 by anamarqu          #+#    #+#             */
/*   Updated: 2023/10/06 11:47:16 by anamarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philosophers.h"

/// //FUNCION del PDF. Duerme un tiempo que se quiera el hilo
int	philo_sleep(t_philo philo, time_t sleep_time)
{
	time_t	wake_up;

	wake_up = get_time_in_ms() + sleep_time;
	while (get_time_in_ms() < wake_up)
	{
		if (philo_die(&philo) == -1)
			return (-1);
		usleep(100);
	}
	return (1);
}

//Filosofo piensa. Tiempo calculado como en el pdf
int	philo_think(t_philo *philo)
{
	time_t	time_to_think;

	time_to_think = (philo->data->time_to_die - (get_time_in_ms()
				- get_time_last_bite(*philo)) - philo->data->time_to_eat) / 2;
	if (time_to_think < 0)
		time_to_think = 0;
	if (time_to_think > 1000)
		time_to_think = 1000;
	if (philo_sleep(*philo, time_to_think) == -1)
		return (-1);
	return (1);
}

int	is_only_one(t_philo *philo)
{
	if (philo->data->num_philos == 1)
	{
		printf("%s%ld %d has taken a fork\n", YELLOW, get_time_in_ms()
			- philo->data->time_start, philo->id + 1);
		if (philo_sleep(*philo, philo->data->time_to_die) == -1)
			return (-1);
		printf("%s%ld %d DIED\n", RED,
			get_time_in_ms() - philo->data->time_start, philo->id + 1);
		set_end_flag(philo->data, 1);
		return (1);
	}
	return (0);
}

int	philo_routine(t_philo *philo)
{
	if (philo_eat(philo) == -1)
		return (-1);
	if (print_state(philo, 2) == -1)
		return (-1);
	if (philo_sleep(*philo, philo->data->time_to_sleep) == -1)
		return (-1);
	if (print_state(philo, 3) == -1)
		return (-1);
	if (philo_think(philo) == -1)
		return (-1);
	if (philo_die(philo) == -1)
		return (-1);
	return (1);
}

//Hilo del philo
void	*thread_philo_routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	set_time_last_bite(philo, get_time_in_ms());
	if (is_only_one(philo))
		return (NULL);
	if (philo->id % 2 == 0)
	{
		if (print_state(philo, 3) == -1)
			return (NULL);
		philo_think(philo);
	}
	while (get_end_flag(*philo->data) == 0)
	{
		usleep(100);
		if (philo_routine(philo) == -1)
			return (NULL);
	}
	return (NULL);
}
