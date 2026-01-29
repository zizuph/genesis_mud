/*
 * who - Tell what players are logged in and who we know
 */
nomask int
index(string str, string letter)
{
    return member_array(letter, explode(str, ""));
}

int
who(string opts, object *list, int size)
{
    int i, j;
    int scrw = (int)this_player()->query_prop(PLAYER_I_SCREEN_WIDTH);
    int see_invis = (int)this_player()->query_prop(LIVE_I_SEE_INVIS);
    string to_write = "", *title, tmp;

    /* We sort automatically to mix in the NPC's. */
    list = sort_array(list, "sort_name", this_object());

    if (scrw == 0)
        scrw = 80;
    scrw -= 3;

    if (!sizeof(list))
    {
        to_write += ("There are no players of the requested type present.\n");
        /* No need to check for mwho here. */
        write(to_write);
        return 1;
    }

    if (size == 1)
        to_write += ("Only one player present.\n");
    else
        to_write += ("There are " + size +
	    " players in the game. Within the requested type you know:\n");

    if (index(opts, "n") > -1)
    {
        to_write += (sprintf("%-*#s\n", scrw,
            implode(map(list, "get_name", this_object(), see_invis) - ({ 0 }),
            "\n")));
        /* No need to check for mwho here. */
        write(to_write);
        return 1;
    }

    for(i = 0; i < sizeof(list); i++)
    {
        tmp = (string)list[i]->query_presentation();

        if (list[i]->query_prop(OBJ_I_INVIS) > see_invis)
        {
            if (this_player()->query_wiz_level())
                to_write += ("(" +
                    capitalize(list[i]->query_real_name()) + ")\n");
        }
        else if (strlen(tmp) < scrw)
        {
            to_write += (tmp + "\n");
        }
        else /* Split a too long title in a nice way. */
        {
            title = explode(break_string(tmp, (scrw - 2)), "\n");
            tmp = sprintf("%-*s\n", scrw, title[0]);

            title = explode(break_string(
                implode(title[1..(sizeof(title) - 1)], " "),
                (scrw - 8)), "\n");

            for(j = 0; j < sizeof(title); j++)
                tmp += (sprintf("      %-*s\n", (scrw - 6), title[j]));

            to_write += (tmp);
        }
    }

    if (query_verb() == "mwho")
    {
        setuid();
        seteuid(getuid());
        clone_object(MORE_OBJ)->more(to_write);
    }
    else
        write(to_write);

    return 1;
}

nomask int
sort_name(object a, object b)
{
    string sa = (string)a->query_real_name();
    string sb = (string)b->query_real_name();

    if (sa < sb)
	return -1;
    if (sa == sb)
	return 0;
    return 1;
}

nomask string
get_name(object player, int see_invis)
{
    if (player->query_prop(OBJ_I_INVIS) > see_invis)
    {
	if (this_player()->query_wiz_level())
	{
	    return ("(" + capitalize(player->query_real_name()) + ")");
	}

	return 0;
    }

    return capitalize(player->query_real_name());
}

/*
 * Function name: real_player
 * Description  : This filter is used to remove login objects from the list.
 * Arguments    : object player - the player to test
 * Returns      : int 1/0       - true if a real living
 */
nomask int
real_player(object player)
{
    return (function_exists("create_container", player) == "/std/living");
}

int
who_known(string opts)
{
    object  *list = users() - ({ 0 });
    object  npc;
    mapping rem;
    string  *names = ({ });
    int     t;
    int     size;

    if (!strlen(opts))
         opts = " ";

    /* This filters for players logging in and such. */
    list = filter(list, "real_player", this_object());

    size = sizeof(list);
    if (index(opts, "w") > -1)
        list = filter(list, "is_wiz", WIZ_CMD_APPRENTICE);
    else if (index(opts, "m") > -1)
	list = filter(list, "not_wiz", WIZ_CMD_APPRENTICE);

    /* Wizards won't see the NPC's */
    if (this_player()->query_wiz_level())
	return who(opts, list, sizeof(list));

    if (mappingp(rem = this_player()->query_remembered()))
        names += m_indices(rem);
    if (mappingp(rem = this_player()->query_introduced()))
        names += m_indices(rem);

#ifdef MET_ACTIVE
    for (t = 0; t < sizeof(list); t++)
    {
	if (!(member_array(list[t]->query_real_name(), names) >= 0 ||
	    list[t]->query_prop(LIVE_I_ALWAYSKNOWN) ||
            list[t] == this_player()))
        {
	    list[t] = 0;
        }
    }

    list = list - ({ 0 });
#endif

    if (index(opts, "w") == -1)
    {
	names -= list->query_real_name();

	for (t = 0; t < sizeof(names); t++)
	{
	    if (objectp(npc = find_living(names[t])))
	    {
		list += ({ npc });
		size++;
	    }
	}
    }

    return who(opts, list, size);
}
