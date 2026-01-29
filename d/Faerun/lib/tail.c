/*
* tail.c
*
* Copyright (C) Stas van der Schaaf - March 20 1998
*               Mercade @ Genesis
*
* This code was developed for the apprentice soul initially, but as separate
* module can also be used to allow players the ability to "tail up" into a
* file. Inherit this module and call the function
*
* void tail_file(string str);
*
* where 'str' is the full path of the file to read.
* 
* Borrowed from Gondor - Nerull 2015.
*/

/*
* Prototype.
*/
private void tail_lines();

/* These properties are used by this object only. */
#define PLAYER_S_TAIL_PATH  "_PLAYER_s_tail_path"
#define PLAYER_I_TAIL_LIMIT "_PLAYER_i_tail_limit"

#define TAIL_READ_CHUNK (800)

/*
* Function name: tail_input_player
* Description  : Input function for the "tail up" command. We call the
*                function tail_lines() if the player wants to see more..
* Arguments    : string str - the input-argument.
*/
nomask void
tail_input_player(string str)
{
	str = (strlen(str) ? lower_case(str) : "u");

	switch (str[0])
	{
	case 'q':
			/* Clean up after ourselves. */
			this_player()->remove_prop(PLAYER_S_TAIL_PATH);
		this_player()->remove_prop(PLAYER_I_TAIL_LIMIT);
		return;

	case 'u':
		tail_lines();
		return;

	default:
		write("Invalid command. \"q\" to quit or RETURN (or \"u\") to " +
			"continue upwards --- ");
		input_to(tail_input_player);
		return;
	}

	write("Impossible end of tail. Please beg for assistance of a wizard.\n");
}

/*
* Function name: tail_lines
* Description  : This function will actually print a part of the file that
*                the person wants to tail.
*/
private void
tail_lines()
{
	string path = this_player()->query_prop(PLAYER_S_TAIL_PATH);
	int    size = file_size(path);
	int    limit = this_player()->query_prop(PLAYER_I_TAIL_LIMIT);
	int    begin = limit - TAIL_READ_CHUNK;
	string text;
	string *lines;

	/* If we reach the begin of the file, stop. */
	if (begin <= 0)
	{
		text = read_bytes(path, 0, limit);
		write(text + "BOF\n");
		this_player()->remove_prop(PLAYER_S_TAIL_PATH);
		this_player()->remove_prop(PLAYER_I_TAIL_LIMIT);
		return;
	}

	text = read_bytes(path, begin, TAIL_READ_CHUNK);
	lines = explode(text, "\n");

	/* If there is at least one line, only print the complete lines. */
	if (sizeof(lines) > 1)
	{
		text = implode(lines[1..], "\n");
	}

	write(text + "\n");
	limit -= (strlen(text) + 1);
	write("TAIL " + limit + "/" + size + " (" + (100 * limit / size) + "%)" +
		" --- \"q\" to quit, RETURN (or \"u\") to continue upwards --- ");

	this_player()->add_prop(PLAYER_I_TAIL_LIMIT, limit);
	input_to(tail_input_player);
}

/*
* Function name: tail_file
* Description  : External function to be called to tail a particular file
*                with the ability to "tail up" into it.
* Arguments    : string path - the full path of the file.
*/
nomask void
tail_file(string path)
{
	int size;

	seteuid(getuid());

	size = file_size(path);
	if (size <= 0)
	{
		write("No such file: " + path + "\n");
		return;
	}

	/* If the file is too small, print the whole file. */
	if (size <= TAIL_READ_CHUNK)
	{
		cat(path);
		return;
	}

	/* Add the relevant information to the player in properties. */
	this_player()->add_prop(PLAYER_S_TAIL_PATH, path);
	this_player()->add_prop(PLAYER_I_TAIL_LIMIT, size);
	tail_lines();
}



























