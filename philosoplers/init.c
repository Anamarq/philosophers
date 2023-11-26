/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamarqu <anamarqu@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 11:47:14 by anamarqu          #+#    #+#             */
/*   Updated: 2023/10/06 11:47:16 by anamarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philosophers.h"

static int	ft_isspace(char c)
{
	if (c == '\f' || c == '\n' || c == '\r'
		|| c == '\t' || c == '\v' || c == ' ')
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	int	sol;
	int	signo;

	signo = 1;
	sol = 0;
	while (ft_isspace(*str))
		++str;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			signo *= -1;
		++str;
	}
	while (*str != '\0' && (*str >= '0' && *str <= '9'))
	{
		sol *= 10;
		sol += *str - '0';
		++str;
	}
	sol *= signo;
	return (sol);
}

t_fork	*init_forks(t_data *data)
{
	t_fork			*forks;
	unsigned int	i;

	forks = malloc(sizeof(t_fork) * (data->num_philos + 1));
	if (!forks)
	{
		free(forks);
		return (NULL);
	}
	i = 0;
	while (i < data->num_philos + 1)
	{
		if (pthread_mutex_init(&forks[i].fork_mutex, NULL) != 0)
			return (NULL);
		forks[i].free_fork = 1;
		++i;
	}
	return (forks);
}

//Inicializa el struct de philos
t_philo	*init_philosophers(t_data *data)
{
	t_philo			*philos;
	unsigned int	i;

	philos = malloc(sizeof(t_philo) * data->num_philos);
	if (!philos)
	{
		free(philos);
		return (NULL);
	}
	i = -1;
	while (++i < data->num_philos)
	{
		philos[i].end_flag = -1;
		if (pthread_mutex_init(&philos[i].end_flag_mutex, NULL) != 0)
			return (NULL);
		if (pthread_mutex_init(&philos[i].time_last_mutex, NULL) != 0)
			return (NULL);
		if (pthread_mutex_init(&philos[i].num_bites_mutex, NULL) != 0)
			return (NULL);
		philos[i].data = data;
		philos[i].id = i;
		philos[i].num_bites = 0;
		philos[i].time_last_bite = get_time_in_ms();
	}
	return (philos);
}

//Inicializa los datos generales
void	*init_data(int argc, char **argv, t_data *data)
{
	data->num_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->num_must_eat = -1;
	data->end_flag = 0;
	if (pthread_mutex_init(&data->end_flag_mutex, NULL) != 0)
		return (NULL);
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
		return (NULL);
	if (argc == 6)
		data->num_must_eat = ft_atoi(argv[5]);
	if (data->time_to_eat == 0)
		data->time_to_eat = 1;
	if (data->time_to_sleep == 0)
		data->time_to_sleep = 1;
	data->forks = init_forks(data);
	data->philos = init_philosophers(data);
	return (NULL);
}
