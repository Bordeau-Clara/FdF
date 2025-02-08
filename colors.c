/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbordeau <cbordeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 11:56:42 by cbordeau          #+#    #+#             */
/*   Updated: 2025/02/08 12:21:30 by cbordeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	find_color(t_data fdf, int base, int final, int i, int j)
{
	if (fdf.coordinate.map[i][j].z <= fdf.coordinate.minz) 
		return (base);
	if (fdf.coordinate.map[i][j].z <= fdf.coordinate.maxz) 
		return (final);

	// Calcul du ratio entre 0 et 1
	float ratio = (float)(fdf.coordinate.map[i][j].z - fdf.coordinate.minz) / (fdf.coordinate.maxz - fdf.coordinate.minz);

	// Extraction des composants R, G, B
	unsigned char r1 = (base >> 16) & 0xFF;
	unsigned char g1 = (base >> 8) & 0xFF;
	unsigned char b1 = base & 0xFF;

	unsigned char r2 = (final >> 16) & 0xFF;
	unsigned char g2 = (final >> 8) & 0xFF;
	unsigned char b2 = final & 0xFF;

	// Interpolation linéaire de chaque canal
	unsigned char r = r1 + (r2 - r1) * ratio;
	unsigned char g = g1 + (g2 - g1) * ratio;
	unsigned char b = b1 + (b2 - b1) * ratio;

	// Reconstruction de la couleur en format 0xRRGGBB
	return (r << 16) | (g << 8) | b;
}

void	change_base_color(t_data *fdf, int base, int final)
{
	int i;
	int j;

	i = 0;
	while (i < fdf->coordinate.maxy)
	{
		j = 0;
		while (j < fdf->coordinate.maxx)
		{
			if (fdf->coordinate.map[i][j].z == fdf->coordinate.minz)
				fdf->coordinate.map[i][j].color = base;
			else
				fdf->coordinate.map[i][j].color = find_color(*fdf, base, final, i, j); 
			j++;
		}
		printf("\n");
		i++;
	}
}
