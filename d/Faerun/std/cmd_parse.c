/*    cmd_parse.c 
 *
 *    Simple example:
 *
 *    add_cmd_parse("[the] 'rune'", "read", "xxx");
 *    add_cmd_parse("[the] [black] 'book'", ({"read", "study"}), "yyy");
 *
 *  Ruthlessly stolen from Krynn modified slightly so it is inheritable.
 *  Praise be to whomever created this! (Rastlin or Aridor is my guess)
 *  Lord Igneous, Sept 1997
 *
 *  Borrowed by Finwe for Faerun. Praise to the Gods above!!
 *  -- Finwe, May 2006
 */




static mapping	gRoom_cmd_map = ([ ]);
static mixed	gRoom_cmds = ({ }), 
gRoom_cmd_parse = ({ });

/*
 * Function:	add_cmd_parse
 * Arguments:	parse: Parse string.
 *		cmd: Commands to give to get the desc.
 *		desc: Description of the item.
 * Description:	Adds a specific item with associated commands to the
 *		room. It is similar to add_cmd_item. But this is using
 *		the parse_command instead to match the args.
 */
public int
add_cmd_parse(string parse, mixed cmd, string desc)
{
    int size, size2, i = -1;

    if (!pointerp(cmd)) cmd = ({ cmd });

    gRoom_cmd_parse += ({ ({ parse, desc }) });

    size = sizeof(cmd);

    size2 = sizeof(gRoom_cmd_parse) - 1;

    while (++i < size)
	if (!pointerp(gRoom_cmd_map[cmd[i]]))
	    gRoom_cmd_map += ([ cmd[i]:({ size2 }) ]);
	else
	    gRoom_cmd_map[cmd[i]] += ({ size2 });

    if (size)
	gRoom_cmds = gRoom_cmds + (cmd - (cmd & gRoom_cmds));
}

/*
 * Function:	cmd_parse_action
 * Arguments:	arg: The string given after the verb
 * Description: Find and execute a command for a specific command item.
 */
public int
cmd_parse_action(string arg)
{
    string vb, desc;
    int *nr_arr, size, i = -1;

    notify_fail(capitalize(query_verb()) +" what?\n");
    if (!arg)
	return 0;

    nr_arr = gRoom_cmd_map[query_verb()];
    size = sizeof(nr_arr);

    while (++i < size)
    {
	if (parse_command(arg, ({}), gRoom_cmd_parse[nr_arr[i]][0]))
	{
	    desc = this_object()->check_call(gRoom_cmd_parse[nr_arr[i]][1]);
	    if (stringp(desc))
	    {
		write(desc);
		return 1;
	    }
	    else
	    {
		if (!desc)
		    continue;
		else
		    return 1;
	    }
	}
    }
    return 0;
}

void
init_cmdparse()
{
    int size, i = -1;

    size = sizeof(gRoom_cmds);

    if (!size)
	return;

    while (++i < size)
	add_action("cmd_parse_action", gRoom_cmds[i]);
}
