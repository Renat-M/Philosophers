/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meourea <meourea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 16:25:56 by meourea           #+#    #+#             */
/*   Updated: 2022/01/29 16:31:18 by meourea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*ft_check_death(void *args)
{
	t_philo	*ph;

	ph = (t_philo *)args;
	while (1)
	{
		pthread_mutex_lock(&ph->last_meal);
		if (ft_get_time() - ph->time_last_meal > ph->info->time_to_die)
		{
			ph->info->output_dead = 1;
			printf("%zu %zu is dead\n", ft_get_time() - ph->info->start_time, \
	ph->philo_id);
			sem_post(ph->info->death);
			pthread_mutex_unlock(&ph->last_meal);
			return (0);
		}
		pthread_mutex_unlock(&ph->last_meal);
		ft_usleep(1);
	}
}

void	ft_life(t_info *info, size_t i)
{
	t_philo	philo;

	philo.info = info;
	philo.philo_id = i + 1;
	philo.nbr_meals = 0;
	philo.time_last_meal = info->start_time;
	if (pthread_mutex_init(&philo.last_meal, NULL))
		exit (0);
	pthread_create(&philo.monitor_tid, NULL, ft_check_death, &philo);
	pthread_detach(philo.monitor_tid);
	while (philo.nbr_meals != info->nbr_meals)
	{
		ft_thinking(&philo);
		ft_eating(&philo);
		ft_sleeping(&philo);
	}
	exit (0);
}

void	ft_thinking(t_philo *ph)
{
	ft_output(ph, "is thinking");
}

void	ft_eating(t_philo *ph)
{
	sem_wait(ph->info->forks);
	ft_output(ph, "has taken a fork");
	sem_wait(ph->info->forks);
	ft_output(ph, "has taken a fork");
	ft_output(ph, "is eating");
	pthread_mutex_lock(&ph->last_meal);
	ph->time_last_meal = ft_get_time();
	pthread_mutex_unlock(&ph->last_meal);
	ft_usleep(ph->info->time_to_eat);
	sem_post(ph->info->forks);
	sem_post(ph->info->forks);
	ph->nbr_meals++;
}

void	ft_sleeping(t_philo *ph)
{
	ft_output(ph, "is sleeping");
	ft_usleep(ph->info->time_to_sleep);
}
