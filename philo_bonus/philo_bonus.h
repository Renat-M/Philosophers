/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meourea <meourea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 14:51:28 by meourea           #+#    #+#             */
/*   Updated: 2022/01/29 16:37:34 by meourea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <string.h>
# include <semaphore.h>
# include <signal.h>

typedef struct s_info
{
	size_t			nbr_philo;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			time_to_die;
	size_t			nbr_meals;
	int				output_dead;
	size_t			start_time;
	size_t			nbr_full;
	sem_t			*output;
	sem_t			*forks;
	sem_t			*death;
	sem_t			*flag_dead;
}				t_info;

typedef struct s_philo
{
	pthread_t		monitor_tid;
	size_t			philo_id;
	t_info			*info;
	size_t			nbr_meals;
	size_t			time_last_meal;
	pthread_mutex_t	last_meal;
}				t_philo;

size_t	ft_atoi(const char *str);
int		ft_error(char *str);
void	ft_life(t_info *info, size_t i);
size_t	ft_get_time(void);
void	ft_output(t_philo *philo, char *str);
void	ft_usleep(size_t time);
int		ft_init_info(int argc, char **argv, t_info *info);
void	ft_init_philo(t_info *info);
void	ft_destroy_sem(t_info *info);
int		ft_init_sem(t_info *info);
void	ft_sleeping(t_philo *ph);
void	ft_eating(t_philo *ph);
void	ft_thinking(t_philo *ph);
void	ft_fork_philo(t_info *info, int *pid);

#endif