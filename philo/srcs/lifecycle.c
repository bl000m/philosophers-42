/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lifecycle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 12:10:00 by mpagani           #+#    #+#             */
/*   Updated: 2023/01/30 18:00:29 by mpagani          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*lifecycle(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->rules->time);
	pthread_mutex_unlock(&philo->rules->time);
	philo->last_meal = philo->rules->start;
	if (philo->n % 2 == 0 && philo->rules->n_philo != 1)
		time_activity(philo->rules->time_to_eat, philo);
	check_death(philo);
	just_one_scenario(philo);
	while ((philo->rules->n_meals != -1 && !check_death(philo)
			&& !check_enough(philo)) || (philo->rules->n_meals == -1
			&& !check_death(philo)))
		activities(philo);
	return (NULL);
}
