/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meourea <meourea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 13:57:35 by meourea           #+#    #+#             */
/*   Updated: 2022/01/28 18:13:32 by meourea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_init_philo(t_philo **philo, t_info *info)
{
	size_t	i;

	i = 0;
	*philo = malloc(sizeof(t_philo) * info->nbr_philo);
	if (!*philo)
		return (1);
	memset(*philo, 0, sizeof(t_philo) * info->nbr_philo);
	while (i < info->nbr_philo)
	{
		(*philo)[i].info = info;
		(*philo)[i].philo_id = i + 1;
		(*philo)[i].l_fork = i;
		if (i != info->nbr_philo - 1)
			(*philo)[i].r_fork = i + 1;
		(*philo)[i].time_last_meal = info->start_time;
		if (pthread_mutex_init(&(*philo)[i].last_meal, NULL))
			return (1);
		if (pthread_mutex_init(&(*philo)[i].full, NULL))
			return (1);
		i++;
	}
	return (0);
}

int	ft_init_mutex(t_info *info)
{
	size_t	i;

	i = 0;
	info->fork = malloc(sizeof(pthread_mutex_t) * info->nbr_philo);
	if (!info->fork)
		return (1);
	while (i < info->nbr_philo)
	{
		if (pthread_mutex_init(&info->fork[i], NULL))
			return (1);
		i++;
	}
	if (pthread_mutex_init(&info->dead, NULL))
		return (1);
	if (pthread_mutex_init(&info->output, NULL))
		return (1);
	if (pthread_mutex_init(&info->all_full, NULL))
		return (1);
	return (0);
}

int	ft_init_info(int argc, char **argv, t_info *info)
{
	info->nbr_philo = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		info->nbr_meals = ft_atoi(argv[5]);
		if (!info->nbr_meals)
			return (1);
	}	
	else
		info->nbr_meals = -1;
	if (!info->nbr_philo || !info->time_to_die || !info->time_to_eat || \
	!info->time_to_sleep)
		return (1);
	info->start_time = ft_get_time();
	return (0);
}

int	ft_init_threads(t_philo *philo, t_info *info)
{
	size_t	i;

	i = 0;
	while (i < info->nbr_philo)
	{
		if (pthread_create(&(philo[i].thread_id), NULL, ft_life, philo + i))
		{	
			ft_free_destroy(&philo, info);
			return (1);
		}
		i++;
	}
	return (0);
}
