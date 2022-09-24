/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meourea <meourea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 13:36:47 by meourea           #+#    #+#             */
/*   Updated: 2022/01/29 12:53:20 by meourea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_free_destroy(t_philo **ph, t_info *info)
{
	size_t	i;

	pthread_mutex_destroy(&info->dead);
	pthread_mutex_destroy(&info->output);
	pthread_mutex_destroy(&info->all_full);
	i = 0;
	while (i < info->nbr_philo)
	{
		pthread_mutex_destroy(&(*ph)[i].last_meal);
		pthread_mutex_destroy(&(*ph)[i].full);
		pthread_mutex_destroy(&info->fork[i]);
		i++;
	}
	if (*ph)
		free(*ph);
	if (info->fork)
		free(info->fork);
}

int	ft_check_full(t_philo *ph, size_t *tmp)
{
	pthread_mutex_lock(&ph->full);
	if (ph->flag_full)
		*tmp = *tmp + 1;
	pthread_mutex_unlock(&ph->full);
	if (*tmp == ph->info->nbr_philo)
	{
		pthread_mutex_lock(&ph->info->all_full);
		ph->info->flag_all_full = 1;
		pthread_mutex_unlock(&ph->info->all_full);
		return (1);
	}
	return (0);
}

int	ft_check_death(t_philo **ph, t_info *info)
{
	size_t	i;
	size_t	tmp;

	tmp = 0;
	i = 0;
	while (i < info->nbr_philo)
	{
		pthread_mutex_lock(&(*ph)[i].last_meal);
		if (ft_get_time() - (*ph)[i].time_last_meal > info->time_to_die)
		{
			pthread_mutex_lock(&info->dead);
			info->flag_dead = 1;
			pthread_mutex_unlock(&info->dead);
			pthread_mutex_unlock(&(*ph)[i].last_meal);
			printf("%zu %zu is dead\n", ft_get_time() - info->start_time, \
	(*ph)[i].philo_id);
			return (1);
		}
		pthread_mutex_unlock(&(*ph)[i].last_meal);
		if (ft_check_full(&(*ph)[i], &tmp))
			return (1);
		i++;
	}
	return (0);
}

void	ft_death_monitor(t_philo **ph, t_info *info)
{
	size_t	i;

	while (1)
	{
		if (ft_check_death(ph, info))
			break ;
	}
	i = 0;
	while (i < info->nbr_philo)
	{
		pthread_join((*ph)[i].thread_id, NULL);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_info	info;
	t_philo	*philos;

	if (argc != 5 && argc != 6)
		return (ft_error("Error: Wrong number of arguments\n"));
	memset(&info, 0, sizeof(t_info));
	if (ft_init_info(argc, argv, &info))
		return (ft_error("Error: init info\n"));
	if (ft_init_mutex(&info))
		return (ft_error("Error: init mutex\n"));
	if (ft_init_philo(&philos, &info))
		return (ft_error("Error: init philo\n"));
	if (ft_init_threads(philos, &info))
		return (ft_error("Error: init trhreads\n"));
	ft_death_monitor(&philos, &info);
	ft_free_destroy(&philos, &info);
	return (0);
}
