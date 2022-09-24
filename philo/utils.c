/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meourea <meourea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 13:33:45 by meourea           #+#    #+#             */
/*   Updated: 2022/01/29 12:52:16 by meourea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_error(char *str)
{
	printf("%s", str);
	return (1);
}

size_t	ft_atoi(const char *str)
{
	int			i;
	size_t		n;

	i = 0;
	n = 0;
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		n = n * 10 + str[i] - 48;
		i++;
	}
	return (n);
}

size_t	ft_get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((size_t)tv.tv_sec * 1000 + (size_t)tv.tv_usec / 1000);
}

void	ft_usleep(size_t time)
{
	size_t	res;

	res = ft_get_time() + time;
	while (ft_get_time() < res)
	{
		usleep(50);
	}
}

void	ft_output(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->info->output);
	pthread_mutex_lock(&philo->info->dead);
	if (philo->info->flag_dead)
	{
		pthread_mutex_unlock(&philo->info->output);
		pthread_mutex_unlock(&philo->info->dead);
		return ;
	}
	pthread_mutex_unlock(&philo->info->dead);
	printf("%zu %zu %s\n", ft_get_time() - philo->info->start_time, \
	philo->philo_id, str);
	pthread_mutex_unlock(&philo->info->output);
}
