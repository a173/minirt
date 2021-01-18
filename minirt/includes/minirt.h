/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaryn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 15:14:53 by acaryn            #+#    #+#             */
/*   Updated: 2020/12/01 15:52:08 by acaryn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# include <math.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# define INT_MAX 2147483647
# define INT_MIN -2147483648
# define TIT "MINI RT by acaryn"
# define BMP "screenshot.bmp"

typedef struct			s_cvc
{
	double				x;
	double				y;
	double				z;
}						t_cvc;

typedef struct			s_camera
{
	t_cvc				*c;
	t_cvc				*v;
	int					g;
	struct s_camera		*prev;
	struct s_camera		*next;
}						t_camera;

typedef struct			s_objects
{
	int					id;
	t_cvc				*c1;
	t_cvc				*c2;
	t_cvc				*c3;
	t_cvc				*rgb;
	double				d;
	double				h;
	t_cvc				*nv;
	struct s_objects	*next;
}						t_objects;

typedef struct			s_copy
{
	int					id;
	t_cvc				c1;
	t_cvc				c2;
	t_cvc				c3;
	t_cvc				rgb;
	double				d;
	double				h;
	double				calc;
	t_cvc				nv;
}						t_copy;

typedef struct			s_all
{
	int					x;
	int					y;
	double				light;
	int					c_cam;
	int					save;
	t_cvc				*rgb;
	t_camera			*camera;
	t_objects			*object;
}						t_all;

typedef struct			s_mlx
{
	void				*mlx;
	void				*win;
	void				*img;
	char				*addr;
	t_all				*all;
	int					x;
	int					y;
	double				light;
	int					pixel;
	int					line;
	int					end;
}						t_mlx;

t_all					*init_all(void);
t_objects				*init_object(int i);
t_camera				*init_camera(void);
t_camera				*add_camera_back(t_camera **lst, t_camera *n);
t_objects				*add_object_back(t_objects **lst, t_objects *n);
int						is_free(t_all *all);

double					sphere(t_cvc *camera, t_cvc *d, t_objects *o, double m);
double					plane(t_cvc *c, t_cvc *d, t_objects *o, double m);
double					triangle(t_cvc *camera, t_cvc *d, t_objects *o,
						double m);
double					square(t_cvc *camera, t_cvc *d, t_objects *o, double m);
double					cylinder(t_cvc *camera, t_cvc *d, t_objects *o,
						double m);
t_cvc					*new_cvc(double x, double y, double z);
int						ft_atoi(char *line, int *nb);
int						ft_atoc(char *line, t_cvc **c);
int						ft_atof(char *line, double *nb);
int						ft_atov(char *line, t_cvc **vc);
t_cvc					v_new(t_cvc v1, t_cvc v2, char c);
double					v_scalar(t_cvc v1, t_cvc v2);
double					v_len(t_cvc v);
t_cvc					v_num(t_cvc *v, double n, char c);
void					cpy_vector(t_cvc *to, t_cvc *from);
void					my_mlx_pixel_put(t_mlx *d, int *x, int *y, int rgb);
int						rgb_to_int(t_cvc rgb);
t_cvc					cam_look(t_cvc *v, t_cvc d);
int						key(int keycode, t_mlx *mlx);
int						key_destroy(t_all *all);
int						ft_strncmp(const char *str1, const char *str2,
						size_t n);
int						error_logs(int error);
int						ft_isdigit(int c);
t_cvc					cross(t_cvc a, t_cvc b);
int						if_clear(t_all *a, char **line, int *ret);
t_cvc					traceray(t_camera *camera, t_cvc d, t_all *a);
int						create_bmp(t_mlx *mlx);

int						skip(char *l, int *i);
int						next(int n, int *i);
int						v_o(t_objects *o);
t_cvc					*nv(t_objects o);
int						write_scr(t_all *a, char *l, int i);
int						write_amb(t_all *a, char *l, int i);
int						write_camera(t_all *a, char *l, int i);
int						write_light(t_all *a, char *l, int i);
int						write_sphere(t_all *a, char *l, int i);
int						write_plane(t_all *a, char *l, int i);
int						write_square(t_all *a, char *l, int i);
int						write_cylinder(t_all *a, char *l, int i);
int						write_triangle(t_all *a, char *l, int i);
int						navigator(t_all *all, char *line, int i);
t_all					*parser(int fd);
void					feel_screen(t_mlx *mlx);

#endif
