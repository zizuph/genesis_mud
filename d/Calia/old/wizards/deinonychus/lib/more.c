static int    more_line,
    	      chunk;

varargs int
more(string file, int start, int size)
{
    object          ob;
    int    more_line, chunk;
    
    more_file = file;

    if (start)
	more_line = start;
    else
	more_line = 1;

    if (size)
	chunk = size;
    else
	chunk = 17;

    if (cat(more_file, more_line, chunk) >= chunk)
    {
	input_to("even_more");
	write("More: --" + (more_line + chunk + 1) + "-- <cr>,d,u,b,#,q> ");
    }
    return 1;
}
static int
even_more(string str)
{
static int    more_line,
    	      chunk;
    int             cnt;

    if (str == "d")
    {
	more_line += 4;
    }
    if (str == "")
    {
	more_line += chunk;
    }
    if (str == "q")
    {
	write("Ok.\n");
	return 1;
    }
    if (str == "b")
    {
	more_line -= 4;
	if (more_line < 1)
	{
	    more_line = 1;
	}
    }
    if (str == "u")
    {
	more_line -= chunk;
	if (more_line < 1)
	{
	    more_line = 1;
	}
    }
    if (str && sscanf(str, "%d", cnt) == 1)
    {
	more_line = cnt;
	if (more_line < 1)
	{
	    more_line = 1;
	}
    }
    if (cat(more_file, more_line, chunk) == 0)
    {
	more_file = 0;
	write("EOF\n");
	return 1;
    }
    write("More: --" + (more_line + chunk) + "-- <cr>,d,u,b,#,q> ");
    input_to("even_more");
    return 1;
}

