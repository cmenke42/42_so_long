/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 20:22:50 by cmenke            #+#    #+#             */
/*   Updated: 2023/04/27 19:49:59 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H

# include "../libft/libft.h"
# include <stdbool.h>
# include <fcntl.h>
# include "../mlx/mlx.h"
# define WALL_IMG "textures/wall2.xpm"
# define PATH_IMG "textures/path.xpm"
# define EXIT_IMG "textures/exit.xpm"
# define PLAYER_IMG "textures/player.xpm"
# define COLLECT_IMG "textures/collectable.xpm"
# define MONSTER_IMG "textures/monster.xpm"
# define MONSTER_TWO_IMG "textures/monster2.xpm"
# define MONSTER_THREE_IMG "textures/monster3.xpm"
# define SCREEN_WTH 1920
# define SCREEN_HGT 1080
# define IMG_WTH 30
# define IMG_HGT 30

typedef struct s_lst
{
	int				y;
	int				x;
	struct s_lst	*next;
}				t_lst;

//arrow keys
enum	e_keys_events
{
	on_keydown = 2,
	win_closed = 17,
	esc = 53,
	arrow_l = 123,
	arrow_r = 124,
	arrow_u = 126,
	arrow_d = 125
};

//mlx_ptr is a big struct from mlx
//height and width are exact
//pov_u -> view range up
//pov_d -> view range down
//pov_l -> view range left
//pov_r -> view range right
typedef struct s_vars
{
	char	*error_text;
	int		exit_code;
	char	**map;
	char	**map_cpy;
	int		map_hgt;
	int		map_wth;
	int		p_pos_y;
	int		p_pos_x;
	int		exit_pos_y;
	int		exit_pos_x;
	int		num_moves;
	int		amt_p;
	int		amt_e;
	int		amt_c;
	int		amt_m;
	int		amt_p_e_c;
	int		taken_c;
	void	*mlx_ptr;
	void	*win_ptr;
	void	*path_img;
	void	*wall_img;
	void	*player_img;
	void	*collect_img;
	void	*exit_img;
	void	*monster_img;
	void	*monster_two_img;
	void	*monster_three_img;
	int		animation_timer;
	int		pov_u;
	int		pov_d;
	int		pov_l;
	int		pov_r;
	int		pov_u_max;
	int		pov_d_max;
	int		pov_l_max;
	int		pov_r_max;
}				t_vars;

//lst_functions
t_lst	*ft_new_node(int row, int col);
t_lst	*ft_last_node(t_lst *lst);
void	ft_node_add_back(t_lst **lst, t_lst *node);
void	ft_clear_lst(t_lst **lst);
//read_map.c
bool	ft_read_map(char *map_name, t_vars *vars);
//check_map_format.c
bool	ft_check_map_name(char *map_name);
bool	ft_check_map_chars(t_vars *vars);
//check_map_path.c
bool	ft_copy_map(t_vars *vars);
bool	ft_find_path(t_vars *vars);
//close_free.c
int		ft_close_window_x(t_vars *vars);
void	ft_free_map(t_vars *vars, int map);
void	ft_close_game(t_vars *vars);
bool	ft_destroy_mlx_images(t_vars *vars);
// calculate_pov.c
void	ft_change_pov_values_on_move(t_vars *vars, int y, int x);
void	ft_get_pov_values(t_vars *vars, int *win_wth, int *win_hgt);
// events_and_key_press.c
int		ft_key_press(int key, t_vars *vars);
// put_map_on_screen.c
bool	ft_create_mlx_images(t_vars *vars, int wth, int hgt);
void	ft_calculate_pov_offset(t_vars *vars, int *y, int *x);
int		ft_render_pov(t_vars *vars, int y_orig, int x_orig);
void	ft_put_movement_counter(t_vars *vars, int num_moves);
// messages.c
bool	ft_error_exit(char	*error_text, int exit_code);
bool	ft_error(char	*error_text, int exit_code);
//monster_sprite.c
bool	ft_create_mlx_images_monster(t_vars *vars, int wth, int hgt);
int		ft_monster_animation(t_vars *vars);
void	ft_animation(t_vars *vars, int y, int x);

#endif