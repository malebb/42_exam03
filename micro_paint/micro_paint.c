#include "micro_paint.h"

int		w;
int		h;
char	bg_c;

void	ft_putstr(char *str)
{
	int		i;


	i = 0;
	while (str[i] != '\0')
	{
		write(1, &str[i], 1);
		i++;
	}
}

int		read_first_line(FILE *file)
{
	if (fscanf(file, "%d %d %c", &w, &h, &bg_c) != 3)
		return (0);
	if (w <= 0 || w > 300 || h <= 0 || h > 300)
		return (0);
	return (1);
}

char	**init_d_zone(char **d_zone)
{
	int		i;

	if (!(d_zone = malloc(sizeof(char *) * (w))))
		return (NULL);
	i = 0;
	while (i < h)
	{
		if (!(d_zone[i] = malloc(sizeof(char) * (w + 1))))
			return (NULL);
		memset(d_zone[i], bg_c, w);
		d_zone[i][w] = '\0';
		i++;
	}
	return (d_zone);
}

void	print_draw(char **d_zone)
{
	int		i;

	i = 0;
	while (i < h)
	{
		ft_putstr(d_zone[i]);
		ft_putstr("\n");
		i++;
	}
}

int		is_int(float nbr)
{
	int		nb;

	nb = (int)nbr;
	if (nbr < 0)
	{
		if ((nbr + nb) == 0)
			return (1);
	}
	else
	{
		if ((nbr - nb) == 0)
			return (1);
	}
	return (0);
}

int		add_rect(FILE *file, char c, char **d_zone)
{
	float	x;
	float	y;
	float	w_r;
	float	h_r;
	char	c_r;
	int		i;
	int		j;
	int		x_min;
	int		y_min;

	if (fscanf(file, "%f %f %f %f %c", &x, &y, &w_r, &h_r, &c_r) != 5)
		return (0);
	if (w_r <= 0 || h_r <= 0)
		return (1);
	if (is_int(y))
	{
		i = y;
		y_min = y;
	}
	else
	{
		i = y + 1;
		y_min = y + 1;
	}
	if (c == 'R')
	{
		while (i <= (int)(y + h_r) && i < h)
		{
			if (is_int(x))
			{
				j = x;
				x_min = x;
			}
			else
			{
				j = x + 1;
				x_min = x + 1;
			}
			while (j <= (int)(x + w_r) && j < w)
			{
				if (i >= 0 && j >= 0)
					d_zone[i][j] = c_r;
				j++;
			}
			i++;
		}
	}
	else
	{
		while (i <= (int)(y + h_r) && i < h)
		{
			if (is_int(x))
			{
				j = x;
				x_min = x;
			}
			else
			{
				j = x + 1;
				x_min = x + 1;
			}
			while (j <= (int)(x + w_r) && j < w)
			{
				if (i == (int)(y + h_r) || i == y_min || j == (int)(x + w_r) || j == x_min)
				{
					if (i >= 0 && j >= 0)
						d_zone[i][j] = c_r;
				}
				j++;
			}
			i++;
		}
	}
	return (1);
}

int		main(int argc, char **argv)
{
	FILE	*file;
	char	**d_zone;
	char	c;

	if (argc != 2)
	{
		ft_putstr("Error: argument\n");
		return (1);
	}
	if (!(file = fopen(argv[1], "r")))
	{
		ft_putstr("Error: Operation file corrupted\n");
		return (1);
	}
	if (!read_first_line(file))
	{
		ft_putstr("Error: Operation file corrupted\n");
		fclose(file);
		return (1);
	}
	d_zone = NULL;
	if (!(d_zone = init_d_zone(d_zone)))
	{
		ft_putstr("Error: Operation file corrupted\n");
		fclose(file);
		return (1);
	}
	while (fscanf(file, "%c", &c) == 1)
	{
		if (c == 'r' || c == 'R')
		{
			if (!add_rect(file, c, d_zone))
			{
				ft_putstr("Error: Operation file corrupted\n");
				fclose(file);
				return (1);
			}
		}
		else if (c != '\n' &&  c != ' ')
		{
			ft_putstr("Error: Operation file corrupted\n");
			fclose(file);
			return (1);
		}
	}
	print_draw(d_zone);
	fclose(file);
}
