/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_map_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iggonzal <iggonzal@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 13:02:48 by iggonzal          #+#    #+#             */
/*   Updated: 2023/08/10 01:24:37 by iggonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static char	*ft_err_message(t_map_vars *map)
{
	if (map->c == 0)
		return (
			"\033[1;31m🛑ERROR: element 'C' is missing\033[0m");
	if (map->p == 0)
		return (
			"\033[1;31m🛑ERROR: element 'P' is missing\033[0m");
	if (map->e == 0)
		return (
			"\033[1;31m🛑ERROR: element 'E' is missing\033[0m");
	if (map->p == 0)
		return (
			"\033[1;31m🛑ERROR: element 'P' is missing\033[0m");
	if (map->p > 1)
		return (
			"\033[1;31m🛑ERROR: there is more then one element 'P'\033[0m");
	return ("\033[1;31m🛑ERROR: element missing in the map\033[0m");
}

char	*unknown_element(t_vars **v, char c)
{
	int	x;

	x = 0;
	while ((*v)->map[x])
	{
		free((*v)->map[x]);
		x++;
	}
	free((*v)->map);
	printf("\033[1;31m🛑ERROR: Unknown element %c \033[0m", c);
	exit(1);
}

void	check_elements(t_vars **v)
{
	t_map_vars	map;

	map.c = 0;
	map.p = 0;
	map.e = 0;
	map.y = get_height((*v)->map) - 1;
	while (map.y--)
	{
		map.x = 0;
		while ((*v)->map[map.y][map.x] != '\0')
		{
			if ((*v)->map[map.y][map.x] == 'E')
				map.e++;
			else if ((*v)->map[map.y][map.x] == 'P')
				map.p++;
			else if ((*v)->map[map.y][map.x] == 'C')
				map.c++;
			else if ((*v)->map[map.y][map.x] != '1' &&
				(*v)->map[map.y][map.x] != '0')
				unknown_element(v, (*v)->map[map.y][map.x]);
			map.x++;
		}
	}
	if (map.c == 0 || map.p == 0 || map.e == 0 || map.p > 1)
		ft_error(v, ft_err_message(&map));
}
