/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabae <dabae@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:25:47 by dabae             #+#    #+#             */
/*   Updated: 2024/10/01 14:25:48 by dabae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

t_vec	add_vec(t_vec a, t_vec b)
{
	t_vec	res;

	res.x = a.x + b.x;
	res.y = a.y + b.y;
	return (res);
}

t_vec	sub_vec(t_vec a, t_vec b)
{
	t_vec	res;

	res.x = a.x - b.x;
	res.y = a.y - b.y;
	return (res);
}

t_vec	scale_vec(t_vec a, double n)
{
	t_vec	res;

	res.x = a.x * n;
	res.y = a.y * n;
	return (res);
}
