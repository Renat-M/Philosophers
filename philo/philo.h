/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meourea <meourea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 13:37:02 by meourea           #+#    #+#             */
/*   Updated: 2022/01/28 18:10:24 by meourea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <string.h>

typedef struct s_info
{
	size_t			nbr_philo;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			time_to_die;
	size_t			nbr_meals;
	int				flag_all_full;
	int				flag_dead;
	size_t			start_time;
	pthread_mutex_t	dead;
	pthread_mutex_t	*fork;
	pthread_mutex_t	output;
	pthread_mutex_t	all_full;
}				t_info;

typedef struct s_philo
{
	pthread_t		thread_id;
	size_t			philo_id;
	t_info			*info;
	size_t			l_fork;
	size_t			r_fork;
	size_t			nbr_meals;
	int				flag_full;
	size_t			time_last_meal;
	pthread_mutex_t	full;
	pthread_mutex_t	last_meal;
}				t_philo;

size_t	ft_atoi(const char *str);
int		ft_error(char *str);
void	*ft_life(void *philo);
size_t	ft_get_time(void);
int		ft_init_philo(t_philo **philo, t_info *info);
int		ft_init_mutex(t_info *info);
int		ft_init_info(int argc, char **argv, t_info *info);
int		ft_init_threads(t_philo *philo, t_info *info);
void	ft_output(t_philo *philo, char *str);
void	ft_usleep(size_t time);
void	ft_free_destroy(t_philo **ph, t_info *info);

#endif
