/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 14:49:34 by mpagani           #+#    #+#             */
/*   Updated: 2023/01/30 18:00:03 by mpagani          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_time	timestamp(void)
{
	struct timeval	timestamp;

	gettimeofday(&timestamp, NULL);
	return ((timestamp.tv_sec * 1000) + (timestamp.tv_usec / 1000));
}

t_time	timestamp_delta(t_philo *philo)
{
	return (timestamp() - philo->rules->start);
}

void	message(t_philo *philo, char flag)
{
	pthread_mutex_lock(&philo->rules->protecting_enough);
	pthread_mutex_lock(&philo->rules->dying);
	pthread_mutex_lock(&philo->rules->message_out);
	if (!philo->rules->someone_is_dead && !philo->rules->eaten_enough)
	{
		if (flag == 'f')
			printf("%05llu %d has taken a fork\n",
				timestamp_delta(philo), philo->n + 1);
		else if (flag == 'e')
			printf("%s%05llu %d is eating%s\n", GREEN,
				timestamp_delta(philo), philo->n + 1, NORMAL);
		else if (flag == 's')
			printf("%05llu %d is sleeping\n",
				timestamp_delta(philo), philo->n + 1);
		else if (flag == 't')
			printf("%05llu %d is thinking\n",
				timestamp_delta(philo), philo->n + 1);
		else if (flag == 'd')
			printf("%s%05llu %d died%s\n", RED,
				timestamp_delta(philo), philo->n + 1, NORMAL);
	}
	pthread_mutex_unlock(&philo->rules->message_out);
	pthread_mutex_unlock(&philo->rules->dying);
	pthread_mutex_unlock(&philo->rules->protecting_enough);
}

void	time_activity(t_time millisec, t_philo *philo)
{
	t_time	start;

	(void) philo;
	start = timestamp();
	if (philo->rules->n_meals != -1)
	{
		while (timestamp() - start < millisec && !check_death(philo)
			&& !check_enough(philo))
			usleep(100);
	}
	else
	{
		while (timestamp() - start < millisec && !check_death(philo))
			usleep(100);
	}
}
