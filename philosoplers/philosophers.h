/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamarqu <anamarqu@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 11:47:14 by anamarqu          #+#    #+#             */
/*   Updated: 2023/10/06 11:47:16 by anamarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <limits.h>

# define NC		"\e[0m"
# define RED	"\e[31m"
# define GREEN	"\e[32m"
# define YELLOW	"\e[33m"
# define BLUE	"\e[34m"
# define PURPLE	"\e[35m"
# define CIAN	"\e[36m"

typedef struct s_philo	t_philo;
typedef struct s_fork	t_fork;
typedef struct s_fork
{
	int				free_fork;
	pthread_mutex_t	fork_mutex;
}	t_fork;

/*
* time_t	time_start;//cuando comienza
pthread_t	thread_controller; //Hilo general
unsigned int num_philos; 
time_t time_to_eat;
time_t	time_to_sleep;
time_t	time_to_die;
int		num_must_eat; //Cuantas veces comer hasta q acabe
//pthread_mutex_t		general_mutex;
t_philo* philos;
t_fork* forks;
int end_flag; //Indica si acaba (si muere un philo o si llega a num_must_eat)
pthread_mutex_t end_flag_mutex;
pthread_mutex_t print_mutex;
*/
typedef struct s_data
{
	time_t			time_start;
	pthread_t		thread_controller;
	unsigned int	num_philos;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	time_t			time_to_die;
	int				num_must_eat;
	t_philo			*philos;
	t_fork			*forks;
	int				end_flag;
	pthread_mutex_t	end_flag_mutex;
	pthread_mutex_t	print_mutex;
}	t_data;

/*
pthread_t	thread; //1 hilo x philo
unsigned int	id; //id x philo (se imprime +1)
t_data *data; //data general
unsigned int	num_bites; //Cuantas veces ha comido cada philo
time_t	time_last_bite; //cuando fue el �ltimo bocao
pthread_mutex_t		time_last_mutex; //Mutex pa el philo
pthread_mutex_t		num_bites_mutex; //Mutex pa el philo
int end_flag; //Indica si acaba (si muere un philo o si llega a num_must_eat)
Si muere acaba sumulaci�n (valor 1), si llega a num_must_eat no acaba (valor 0)
pthread_mutex_t end_flag_mutex;
*/

typedef struct s_philo
{
	pthread_t		thread;
	unsigned int	id;
	t_data			*data;
	unsigned int	num_bites;
	time_t			time_last_bite;
	pthread_mutex_t	time_last_mutex;
	pthread_mutex_t	num_bites_mutex;
	int				end_flag;
	pthread_mutex_t	end_flag_mutex;
}	t_philo;

void			*init_data(int argc, char **argv, t_data *data);
int				check_input(int argc, char *argv[]);
int				print_state(t_philo *philo, int state);
void			*controller(void *_data);
int				philo_sleep(t_philo philo, time_t sleep_time);
void			*thread_philo_routine(void *data);
int				philo_eat(t_philo *philo);
int				philo_die(t_philo *philo);
int				join_threads(t_data *data);
//get and set
time_t			get_time_in_ms(void);
int				get_fork(t_fork fork);
void			set_fork(t_fork *fork, int is_free);
time_t			get_time_last_bite(t_philo philo);
void			set_time_last_bite(t_philo *philo, time_t time);
unsigned int	get_num_eat(t_philo philo);
void			set_num_eat(t_philo *philo, unsigned int num);
int				get_philo_end_flag(t_philo data);
void			set_philo_end_flag(t_philo *data, int num);
int				get_end_flag(t_data data);
void			set_end_flag(t_data *data, int num);

#endif