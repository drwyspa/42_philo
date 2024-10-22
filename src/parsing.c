/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjedrycz <p.jedryczkowski@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 22:10:04 by pjedrycz          #+#    #+#             */
/*   Updated: 2024/10/17 22:29:05 by pjedrycz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* 
	Checks if the strings contains only digits (from 0 to 9).
	Return true if yes and false if some char in the string
	is not a digit.
*/
static bool	digits_only(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str [i] < 48 || str[i] > 57)
			return (false);
		i++;
	}
	return (true);
}

/*
	Simplified atoi - converts digits only string into a positive int.
	Return number between 0 and INT_MAX.
	Or -1 if the converted number exceeds INT_MAX.
*/
int	atoi_int(char *str)
{
	unsigned long long int	nb;
	int						i;

	i = 0;
	nb = 0;
	while (str[i] && (str[i] >= 48 && str[i] <= 57))
	{
		nb = (nb * 10) + (str[i] - 48);
		i++;
	}
}

/* 
	Input validation.
	Check all required arguments:
	- only digits in the string given,
	- all digits are not exceed INT_MAX,
	- and are between 1 and MAX_PHILOS value.
	Return true for valid arguments and false for invalid.
*/
bool	is_valid_input(int argc, char **argv)
{
	int	i;
	int	nb;

	i = 1;
	while (i < argc)
	{
		if (!digits_only(argv[i]))
			return (msg(STR_ERR_INPUT_DIGIT, argv[i], false));
		nb = atoi_int(argv[i]);
		if (i == 1 && (nb <= 0 || nb >= MAX_PHILOS))
			return (msg(STR_ERR_INPUT_POFLOW, STR_MAX_PHILOS, false));
		if (i != 1 && nb == -1)
			return (msg(STR_ERR_INPUT_DIGIT, argv[i], false));
		i++;
	}
	return (true);
}
