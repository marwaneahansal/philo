/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahansal <mahansal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 16:42:07 by mahansal          #+#    #+#             */
/*   Updated: 2023/05/04 15:24:43 by mahansal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t	length;

	length = 0;
	while (s[length] != '\0')
		length++;
	return (length);
}

char	*ft_strdup(const char *s1)
{
	char	*dst;
	int		index;
	size_t	dst_len;

	dst_len = ft_strlen(s1);
	dst = (char *) malloc((dst_len + 1) * sizeof(char));
	index = 0;
	if (dst == 0)
		return (0);
	while (s1[index] != '\0')
	{
		dst[index] = s1[index];
		index++;
	}
	dst[index] = '\0';
	return (dst);
}

static int	count_digits(int number)
{
	int	digits_count;

	digits_count = 1;
	while (number > 9)
	{
		number /= 10;
		digits_count++;
	}
	return (digits_count);
}

static char	*set_number(char *str, int sign, int digits_count, int number)
{
	int	index;

	index = digits_count;
	if (sign == 1)
	{
		while (index > 0)
		{
			str[index] = number % 10 + '0';
			number = number / 10;
			index--;
		}
		str[0] = '-';
	}
	else
	{
		index -= 1;
		while (index >= 0)
		{
			str[index] = number % 10 + '0';
			number = number / 10;
			index--;
		}
	}
	str[digits_count + sign] = '\0';
	return (str);
}

char	*ft_itoa(int n)
{
	int		digits_count;
	int		sign;
	int		number;
	char	*str;

	sign = 0;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n < 0)
	{
		n *= -1;
		sign = 1;
	}
	number = n;
	digits_count = count_digits(number);
	str = malloc((digits_count + sign + 1) * sizeof(char));
	if (!str)
		return (0);
	return (set_number(str, sign, digits_count, number));
}
