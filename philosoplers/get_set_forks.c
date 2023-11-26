/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_set_forks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamarqu <anamarqu@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 11:47:14 by anamarqu          #+#    #+#             */
/*   Updated: 2023/10/06 11:47:16 by anamarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philosophers.h"

int	get_fork(t_fork fork)
{
	int	is_free;

	pthread_mutex_lock(&fork.fork_mutex);
	is_free = fork.free_fork;
	pthread_mutex_unlock(&fork.fork_mutex);
	return (is_free);
}

void	set_fork(t_fork *fork, int is_free)
{
	pthread_mutex_lock(&fork->fork_mutex);
	fork->free_fork = is_free;
	pthread_mutex_unlock(&fork->fork_mutex);
}
