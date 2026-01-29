/* 
 * /std/room/move.c
 *
 * This is a sub-part of /std/room.c
 *
 * It handles loading rooms and moving between rooms.
 */
#pragma no_clone
#pragma strict_types
#pragma save_binary

#ifndef DEF_DIRS
#define DEF_DIRS ({ "north", "northeast", "east", "southeast", "south", \
                    "southwest", "west", "northwest", })
#endif

static mapping fail_exits = ([]);  /* This variable must be initialized */

/*
 * Function name: unq_no_move
 * Description  : This function here so that people who try to walk into a
 *                'normal', but nonexistant direction get a proper fail
 *                message rather than the obnoxious "What?". Here, 'normal'
 *                exits are north, southeast, down, excetera.
 * Arguments    : string str - the command line argument.
 * Returns      : int 0/1.
 * Notes	: This will parse VBFC. If you use VBFC, you must either
 * 		  return a string message that will get passed to notify_fail,
 * 		  otherwise print your own message and return '1'.
 */
public int
unq_no_move(string str = query_verb())
{
    if (fail_exits[str])
    {
	mixed res = this_object()->check_call(fail_exits[str]);

	if (stringp(res))
	    return notify_fail(res);
	else
	    return res;
    }
    else
    {
        return notify_fail("There is no obvious exit "+ str +".\n");
    }
}

/*
 * Function name: add_fail
 * Description  : This function is so you may customize your fail exit
 *                messages. This is done by giving a message you want to
 *                be displayed if someone goes in that direction.
 * Arguments    : mixed dir - String or string array of fail exits to add.
 *                varargs   - Specify one additional argument per failed
 *                            exit to receive that message.
 *                            If only one extra arg is specified, it
 *                            will be used for all exits in 'dir'.
 * Notes	: If 'dir' is equal to "auto", then the function will
 * 		  assign the failure message to all exits that haven't
 * 		  already been defined via add_exit().  This only covers
 * 		  the standard 8 compass point directions.
 */
public varargs void
add_fail(mixed dir, ...)
{
    int size, sizev;

    if (stringp(dir))
    {
	if (dir == "auto")
	{
	    dir = DEF_DIRS - (string *)this_object()->query_exit_cmds();
	}
	else
	{
	    dir = ({ dir });
	}
    }

    if (!pointerp(dir))
        return;

    if (!(sizev = sizeof(argv)))
        return;

    size = sizeof(dir);
    if (size > sizev && sizev != 1)
    {
        sizev = size - sizev;
        argv += allocate(sizev);
    }

    while(size--)
    {
        fail_exits[dir[size]] = (sizev == 1 ? argv[0] : argv[size]);
    }
}

/*
 * Function name: remove_fail
 * Description  : Use this function to delete a previously customized fail
 *                exit message.
 * Arguments    : mixed dir - String or string array of exits to remove.
 */
public varargs void
remove_fail(mixed dir)
{
    int size;

    if (stringp(dir))
        dir = ({ dir });

    if (!pointerp(dir))
        return;
    
    size = sizeof(dir);
    while(size--)
    {
        fail_exits = m_delete(fail_exits, dir[size]);
    }
}

/*
 * Function name: query_fail_exit
 * Description  : This is so you may query the different fail exit
 *                commands and their associated messages.
 * Arguments    : mixed arg :
 *                  (string) enter a direction string and it
 *                           will return the message associated with it.
 *                  (int) 1 = return an array of fail exit dirs. (def)
 *                  (int) 2 = return an array of fail exit messages.
 *                  (int) -1 = return array of dirs and messages.
 * Returns      : string * - return dirs, messages, or specific message.
 */
public string *
query_fail_exit(mixed arg = 1)
{
    if (stringp(arg))
    {
        if (member_array(arg, m_indices(fail_exits)) != -1)
            return ({ arg, fail_exits[arg] });
        else
            return ({});
    }

    switch(arg)
    {
    case -1:
        return ({ m_indices(fail_exits), m_values(fail_exits) });
    case 1:
        return m_indices(fail_exits);
    case 2:
        return m_values(fail_exits);
    default:
	return ({});
    }
}

