#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

int		h;
int		w;
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
	if (w <= 0 || h <= 0 || w > 300 || h > 300)
		return (0);
	return (1);
}

char	**init_d_zone(char **d_zone)
{
	int		i;

	if (!(d_zone = malloc(sizeof(char *) * (h))))
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

int		add_circle(FILE *file, char c, char **d_zone)
{
	float	x;
	float	y;
	float	rad;
	char	c_c;
	int		i;
	int		j;

	if (fscanf(file, "%f %f %f %c", &x, &y, &rad, &c_c ) != 4)
		return (0);
	if (x < 0 || y < 0)
		return (1);
	if (rad <= 0)
		return (0);
	if (c == 'C')
	{
		i = 0;
		while (i < h)
		{
			j = 0;
			while (j < w)
			{
				if (sqrt(powf((i - y), 2) + powf((j - x), 2)) <= rad)
					d_zone[i][j] = c_c;
					j++;
			}
			i++;
		}
	}
	else
	{
		i = 0;
		while (i < h)
		{
			j = 0;
			while (j < w)
			{
				if (sqrt(powf((i - y), 2) + powf((j - x), 2)) <= rad && sqrt(powf((i - y), 2) + powf((j - x), 2)) > rad - 1)
					d_zone[i][j] = c_c;
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
		if (c == 'c' || c == 'C')
		{
			if (!add_circle(file, c, d_zone))
			{
				ft_putstr("Error: Operation file corrupted\n");
				fclose(file);
				return (1);
			}
		}
		else if (c != ' ' && c != '\n')
		{
			ft_putstr("Error: Operation file corrupted\n");
			fclose(file);
			return (1);
		}
	}
	print_draw(d_zone);
	fclose(file);
	return (0);
}
