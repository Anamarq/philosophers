/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamarqu <anamarqu@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 11:47:14 by anamarqu          #+#    #+#             */
/*   Updated: 2023/10/06 11:47:16 by anamarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philosophers.h"

int	philo_die(t_philo *philo)
{
	if (((get_time_in_ms() - get_time_last_bite(*philo))
			>= philo->data->time_to_die) && (get_end_flag(*philo->data) == 0))
	{
		print_state(philo, 4);
		set_end_flag(philo->data, 1);
		return (-1);
	}
	return (1);
}

unsigned int	get_id2(t_philo *philo)
{
	unsigned int	idfork2;

	if (philo->id == philo->data->num_philos - 1)
		idfork2 = 0;
	else
		idfork2 = philo->id + 1;
	return (idfork2);
}

int	wait_fork(t_philo *philo, int id)
{
	while (get_fork(philo->data->forks[id]) != 1)
	{
		usleep(500);
		if (philo_die(philo) == -1)
			return (-1);
	}
	return (1);
}

int	start_eat(t_philo *philo, int idfork2)
{
	unsigned int	num_eat;

	set_fork(&philo->data->forks[idfork2], 0);
	if (print_state(philo, 1) == -1)
		return (-1);
	set_time_last_bite(philo, get_time_in_ms());
	if (philo_sleep(*philo, philo->data->time_to_eat) == -1)
		return (-1);
	num_eat = get_num_eat(*philo);
	set_num_eat(philo, num_eat + 1);
	set_fork(&philo->data->forks[philo->id], 1);
	set_fork(&philo->data->forks[idfork2], 1);
	return (1);
}

//Filosofo come.Hecho como lo explicado en el pfd
int	philo_eat(t_philo *philo)
{
	unsigned int	idfork2;

	idfork2 = get_id2(philo);
	if (wait_fork(philo, philo->id) == -1)
		return (-1);
	if ((get_fork(philo->data->forks[philo->id]) == 1))
	{
		set_fork(&philo->data->forks[philo->id], 0);
		if (print_state(philo, 0) == -1)
			return (-1);
		if (wait_fork(philo, idfork2) == -1)
			return (-1);
		if (get_fork(philo->data->forks[idfork2]) == 1)
		{
			if (start_eat(philo, idfork2) == -1)
				return (-1);
		}
	}
	return (1);
}
