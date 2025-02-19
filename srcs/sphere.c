/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbordeau <cbordeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 10:17:22 by cbordeau          #+#    #+#             */
/*   Updated: 2025/02/19 09:15:58 by cbordeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

/*t_point	project_spherical(t_data fdf, int x, int y)
{
	t_point		result;
	t_vector	rot;
	float		r, theta, phi;
	float		x_cart, y_cart, z_cart;

	// Ajustement pour recentrer la grille avant projection
	float center_x = fdf.coordinate.maxx / 2.0;
	float center_y = fdf.coordinate.maxy / 2.0;

	// Récupération des coordonnées initiales
	z_cart = -fdf.coordinate.map[y][x].z * fdf.step; // Inversion de Z pour les reliefs
	x_cart = (x - center_x) * fdf.step; // Centrage horizontal
	y_cart = (y - center_y) * fdf.step; // Centrage vertical

	// Rayon de la sphère virtuelle
	float sphere_radius = fmax(fdf.coordinate.maxx, fdf.coordinate.maxy) * fdf.step / 1.5;

	// Nouvelle distance r avec Z inversé
	r = sqrt(x_cart * x_cart + y_cart * y_cart + z_cart * z_cart);
	theta = atan2(y_cart, x_cart); // Angle XY
	phi = asin(z_cart / (r + 0.0001)); // Angle vertical

	// Projection sur la sphère
	rot.x = sphere_radius * cos(phi) * cos(theta);
	rot.y = sphere_radius * cos(phi) * sin(theta);

	// Ajustement pour recentrer l'affichage
	result.x = round(fdf.translatex + 900 + rot.x);
	result.y = round(fdf.translatey + 540 + rot.y);
	result.color = fdf.coordinate.map[y][x].color;

	return (result);
}*/

// t_point	project_spherical(t_data fdf, int x, int y)
// {
// 	t_point		result;
// 	t_vector	rot;
// 	float		r, theta, phi;
// 	float		x_cart, y_cart, z_cart;
//
// 	// Centrage des coordonnées pour éviter les décalages
// 	float center_x = fdf.coordinate.maxx / 2.0;
// 	float center_y = fdf.coordinate.maxy / 2.0;
//
// 	// Transformation en coordonnées cartésiennes
// 	x_cart = (x - center_x) * fdf.step;
// 	y_cart = (y - center_y) * fdf.step;
// 	z_cart = fdf.coordinate.map[y][x].z * fdf.step;
//
// 	// Rayon de la sphère basé sur la taille de la map
// 	float base_radius = fmax(fdf.coordinate.maxx, fdf.coordinate.maxy) * fdf.step / 2.0;
// 	r = base_radius + z_cart;  // 🔥 Ajout du relief
//
// 	// Calcul des angles sphériques
// 	theta = atan2(y_cart, x_cart);    // Angle horizontal
// 	phi = acos(z_cart / r);           // Angle vertical
//
// 	// **Condition pour ne pas afficher les points derrière la sphère**
// 	if (z_cart < -base_radius * 0.2)  // 🔥 Condition ajustée
// 		return ((t_point){-1, -1, 0}); // 🔥 Ignore le point
//
// 	// Projection sur la sphère
// 	rot.x = r * sin(phi) * cos(theta);
// 	rot.y = r * sin(phi) * sin(theta);
//
// 	// Ajustement final et stockage du point projeté
// 	result.x = round(fdf.translatex + 900 + rot.x);
// 	result.y = round(fdf.translatey + 540 + rot.y);
// 	result.color = fdf.coordinate.map[y][x].color;
//
// 	return (result);
// }



// t_point	project_cylindrical(t_data fdf, int x, int y)
// {
// 	t_point		result;
// 	t_vector	rot;
// 	float		radius;
// 	float		theta;
//
// 	// Centre de la carte
// 	float center_x = fdf.coordinate.maxx / 2.0;
// 	float center_y = fdf.coordinate.maxy / 2.0;
//
// 	// Convertir en coordonnées cartésiennes centrées
// 	float x_cart = (x - center_x) * fdf.step;
// 	float y_cart = (y - center_y) * fdf.step;
// 	float z_cart = fdf.coordinate.map[y][x].z * fdf.step;
//
// 	// Rayon du cylindre (basé sur la largeur de la map)
// 	radius = (fdf.coordinate.maxx * fdf.step) / (2 * M_PI); 
//
// 	// Conversion en coordonnées cylindriques
// 	theta = x_cart / radius;  // Angle proportionnel à x
// 	rot.x = radius * sin(theta);  
// 	rot.y = radius * cos(theta);
// 	rot.z = y_cart + z_cart;  // Garder la hauteur intacte
//
// 	// Projection finale en 2D
// 	result.x = round(fdf.translatex + 800 + rot.x);
// 	result.y = round(fdf.translatey + 540 + rot.z);
// 	result.color = fdf.coordinate.map[y][x].color;
//
// 	return (result);
// }


t_point project_stereographic(t_data fdf, int x, int y)
{
    t_point result;
    float center_x = fdf.coordinate.maxx / 2.0;
    float center_y = fdf.coordinate.maxy / 2.0;

    // Normalisation des coordonnées (centrage)
    float x_cart = (x - center_x) * fdf.step;
    float y_cart = (y - center_y) * fdf.step;
    float z_cart = fdf.coordinate.map[y][x].z * fdf.step;

    // Conversion en coordonnées sphériques
    float r = sqrt(x_cart * x_cart + y_cart * y_cart + z_cart * z_cart);
    float theta = atan2(y_cart, x_cart);  // Angle azimutal
    float phi = acos(z_cart / r);         // Angle de hauteur

    // Projection stéréographique
    float k = 1.0 / (1.0 + cos(phi));  // Facteur de projection

    result.x = round(fdf.translatex + 800 + (k * r * sin(theta)));
    result.y = round(fdf.translatey + 540 + (k * r * cos(theta)));
    result.color = fdf.coordinate.map[y][x].color;

    return (result);
}
typedef struct s_circle
{
	float	r;
	float	theta;
	float	phi;
	int		color;
}t_circle;

t_point	project_spherical(t_data fdf, int x, int y)
{
	t_point		result;
	t_vector	rot;
	t_circle	circle;

	circle.r = sqrt(x * x + y * y + fdf.coordinate.map[y][x].z * fdf.coordinate.map[y][x].z);
	circle.theta = atan2(y, x);
	if (circle.r == 0)
		circle.phi = 0;
	else
		circle.phi = acos(fdf.coordinate.map[y][x].z / circle.r);
	rot.x = circle.r * cos(circle.theta) * sin(circle.phi);
	rot.y = circle.r * sin(circle.theta) * sin(circle.phi);
	// Ajustement final et stockage du point projeté
	result.x = round(fdf.translatex + 900 + rot.x);
	result.y = round(fdf.translatey + 540 + rot.y);
	result.color = fdf.coordinate.map[y][x].color;

	return (result);
}

void	ft_draw_square2(t_data *fdf, t_coordinate coordinate, int x, int y)
{
	t_point	next;
	t_point	current;

	set_angle(fdf);
	fdf->offset = set_offset(*fdf);
	while (x < coordinate.maxx)
	{
		y = 0;
		while (y < coordinate.maxy)
		{
			current = project_stereographic(*fdf, x, y);
			if (x < coordinate.maxx - 1)
			{
				next = project_stereographic(*fdf, x + 1, y);
				ft_draw_line(fdf, current, next);
			}
			if (y < coordinate.maxy - 1)
			{
				next = project_stereographic(*fdf, x, y + 1);
				ft_draw_line(fdf, current, next);
			}
			y++;
		}
		x++;
	}
}
