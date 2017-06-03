int		main(void)
{
	char *line;
	t_a abyss;

	abyss.head = NULL;
	abyss.start = NULL;
	abyss.end = NULL;
	abyss.ants = 0;
	abyss.node_count = 2;
	line = NULL;
	abyss.flag = 0;
	abyss.routes = NULL;
	abyss.test_route = NULL;
	abyss.visit = NULL;
	abyss.best = NULL;
	abyss.priority = 0;
	abyss.matrix = NULL;
	abyss.names = NULL;
	ft_read_ants(&line, &abyss);
	if (!(abyss.flag = ft_read_rooms(&line, &abyss)))
	{
		c_destruct(&abyss);
		write(1, "ERROR\n", 6);
		exit(-2);
	}
	start_end_to_list(&abyss);
	validate_room_names_coords(&abyss, &line);
	if (!matrix_init(&abyss))
	{
		c_destruct(&abyss);
		write(1, "Not enough memory\n", 18);
		exit(-3);
	}
	if (!names_init(&abyss))
	{
		c_destruct(&abyss);
		write(1, "Not enough memory\n", 18);
		exit(-3);
	}
	if (!ft_read_links(&line, &abyss))
	{
		ft_strdel(&line);
		c_destruct(&abyss);
		write(1, "ERROR\n", 6);
		exit(-4);
	}

	for (int i = 0; i < abyss.node_count; i++)
	{
		for (int j = 0; j < abyss.node_count; j++)
		{
			printf(" %d ", abyss.matrix[i][j]);
		}
		printf("\n");
	}

	for (int i = 0; i < abyss.node_count; i++)
	{
		printf("|%s|\n", abyss.names[i]);
	}
	
	finding_path(&abyss);
	if (abyss.routes == NULL)
	{
		write(1, "ERROR\n", 6);
		exit(-4);
	}


	t_way *lal = abyss.routes;
	t_route *huy;
	while (lal != NULL)
	{
		huy = lal->head;
		while (huy != NULL)
		{
			printf("|%d| - ", huy->room_index);
			huy = huy->next;
		}
		printf("\n");
		lal = lal->next;
	}
	printf("\n");
	sorting_routes(&abyss);

	lal = abyss.routes;
	while (lal != NULL)
	{
		huy = lal->head;
		while (huy != NULL)
		{
			printf("|%d| - ", huy->room_index);
			huy = huy->next;
		}
		printf("\n");
		lal = lal->next;
	}

	set_search(abyss.routes, &abyss);
	remove_odd_routes(&abyss);

	lal = abyss.routes;
	while (lal != NULL)
	{
		huy = lal->head;
		while (huy != NULL)
		{
			printf("|%d| - ", huy->room_index);
			huy = huy->next;
		}
		printf("\n");
		lal = lal->next;
	}

	moving_ants(&abyss);

	c_destruct(&abyss);

	return (0);
}