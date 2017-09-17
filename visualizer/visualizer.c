#include "visualizer.h"

int main(int argc, char **argv)
{
	char	*file;
	int		num;
	// signal(SIGINT, sigint_handler);

	if (argc < 2)
	{
		printf("Usage:\nPlease specify a valid filename as the second argument.\n");
		return (-1);
	}
	num = 1;
	while (num < argc)
	{
		setup_screen();
		file = argv[num];
		if ((fd = open_file(file)) < 0)
		{
			printf("Open failed!\n");
			return (-1);
		}
		cleanup_screan();
	}
	return (1);
}

int	setup_screen()
{
	initscr();
	raw();
	return (1);
}

int	cleanup_screen();
{
	getch();
	endwin();
	return (1);
}

int open_file(char *file)
{
	int fd;

	fd = open(file, O_RDONLY);
	return (fd);
}

