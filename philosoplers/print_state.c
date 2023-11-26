/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamarqu <anamarqu@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 16:07:34 by anamarqu          #+#    #+#             */
/*   Updated: 2023/10/06 16:07:35 by anamarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philosophers.h"

void	print_state2(t_philo *philo, int state)
{
	printf("%s%ld %d has taken a fork\n", YELLOW, get_time_in_ms()
		- philo->data->time_start, philo->id + 1);
	if (state == 1)
		printf("%s%ld %d is eating\n", GREEN, get_time_in_ms()
			- philo->data->time_start, philo->id + 1);
}

int	print_state(t_philo *philo, int state)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	if (get_end_flag(*philo->data) != 0)
	{
		pthread_mutex_unlock(&philo->data->print_mutex);
		return (-1);
	}
	if (state == 0 || state == 1)
		print_state2(philo, state);
	else if (state == 2)
		printf("%s%ld %d is sleeping\n", CIAN, get_time_in_ms()
			- philo->data->time_start, philo->id + 1);
	else if (state == 3)
		printf("%s%ld %d is thinking\n", PURPLE, get_time_in_ms()
			- philo->data->time_start, philo->id + 1);
	else if (state == 4)
	{
		printf("%s%ld %d DIED\n", RED, get_time_in_ms()
			- philo->data->time_start, philo->id + 1);
	}
	pthread_mutex_unlock(&philo->data->print_mutex);
	return (1);
}
