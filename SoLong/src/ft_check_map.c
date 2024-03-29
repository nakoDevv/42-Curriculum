/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iggonzal <iggonzal@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 13:02:56 by iggonzal          #+#    #+#             */
/*   Updated: 2023/08/10 01:25:30 by iggonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_error(t_vars **v, char *err)
{
	int	x;

	x = 0;
	while ((*v)->map[x])
	{
		free((*v)->map[x]);
		x++;
	}
	free((*v)->map);
	printf("%s", err);
	exit(1);
}

static void	check_is_rectangular(t_vars **v)
{
	int	y_map;
	int	x_map;
	int	height;
	int	backup;

	y_map = 0;
	backup = 0;
	height = get_height((*v)->map);
	while (y_map != height)
	{
		x_map = 0;
		while ((*v)->map[y_map][x_map] != '\0')
			x_map++;
		y_map++;
		if (backup != 0)
		{
			if (backup != x_map)
				ft_error(v,
					"\033[1;31m🛑ERROR: map is not rectangular\033[0m");
		}
		else
			backup = x_map;
	}
}

static int	check_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] != '1')
			return (1);
		i++;
	}
	return (0);
}

static void	check_surrounded_by_walls(t_vars **v)
{
	int		i;
	char	*err;

	err = "\033[1;31m🛑ERROR: map is not surrounded by walls\033[0m";
	if (check_line((*v)->map[0]))
		ft_error(v, err);
	i = get_height((*v)->map) - 1;
	while (i)
	{
		if ((*v)->map[i][0] != '1' ||
			(*v)->map[i][ft_strlen((*v)->map[i]) - 1] != '1')
		{
			ft_error(v, err);
		}
		i--;
	}
	if (check_line((*v)->map[get_height((*v)->map) - 1]))
		ft_error(v, err);
}

void	check_map_valid(t_vars *v)
{
	check_is_rectangular(&v);
	check_surrounded_by_walls(&v);
	check_elements(&v);
}
