/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_set_times_and_eat.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamarqu <anamarqu@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 11:47:14 by anamarqu          #+#    #+#             */
/*   Updated: 2023/10/06 11:47:16 by anamarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philosophers.h"

time_t	get_time_last_bite(t_philo philo)
{
	time_t	time;

	pthread_mutex_lock(&philo.time_last_mutex);
	time = philo.time_last_bite;
	pthread_mutex_unlock(&philo.time_last_mutex);
	return (time);
}

void	set_time_last_bite(t_philo *philo, time_t time)
{
	pthread_mutex_lock(&philo->time_last_mutex);
	philo->time_last_bite = time;
	pthread_mutex_unlock(&philo->time_last_mutex);
}

unsigned int	get_num_eat(t_philo philo)
{
	unsigned int	num;

	pthread_mutex_lock(&philo.num_bites_mutex);
	num = philo.num_bites;
	pthread_mutex_unlock(&philo.num_bites_mutex);
	return (num);
}

void	set_num_eat(t_philo *philo, unsigned int num)
{
	pthread_mutex_lock(&philo->num_bites_mutex);
	philo->num_bites = num;
	pthread_mutex_unlock(&philo->num_bites_mutex);
}

// Function that returns the current time since the 
// 1st of January 1970 in milliseconds
//FUNCION del PDF. Devuelve el tiempo
time_t	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
