/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_set_flags.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamarqu <anamarqu@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 11:47:14 by anamarqu          #+#    #+#             */
/*   Updated: 2023/10/06 11:47:16 by anamarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philosophers.h"

int	get_philo_end_flag(t_philo data)
{
	int	num;

	pthread_mutex_lock(&data.end_flag_mutex);
	num = data.end_flag;
	pthread_mutex_unlock(&data.end_flag_mutex);
	return (num);
}

void	set_philo_end_flag(t_philo *data, int num)
{
	pthread_mutex_lock(&data->end_flag_mutex);
	data->end_flag = num;
	pthread_mutex_unlock(&data->end_flag_mutex);
}

int	get_end_flag(t_data data)
{
	int	num;

	pthread_mutex_lock(&data.end_flag_mutex);
	num = data.end_flag;
	pthread_mutex_unlock(&data.end_flag_mutex);
	return (num);
}

void	set_end_flag(t_data *data, int num)
{
	pthread_mutex_lock(&data->end_flag_mutex);
	data->end_flag = num;
	pthread_mutex_unlock(&data->end_flag_mutex);
}
