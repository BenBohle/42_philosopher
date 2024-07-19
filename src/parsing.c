int is_not_number(char *str) {
	int counter;

	counter = 0;
	while (str[counter] != '\0')
	{
		if (str[counter] < '0' || str[counter] > '9')
			return 1;
		counter++;
	}
	return 0;
}

int check_input(int argc, char **argv) {
	int counter;

	if (argc < 5 || argc > 6) {
		return 1;
	}

	counter = 1;
	while (counter < argc)
	{
		if (is_not_number(argv[counter]) == 1)
			return 1;
		counter++;
	}
	
	return 0;
}