/*    /d/Krynn/std/room/search.c
 *
 *    add_search("here for gold", 15, "/d/Krynn/xxx/gold", 2);
 *    add_search(({"here for stone", "here for stones"}), 11,
 *		   "You can't find any stones here.\n"); 
 *    add_search("here", 3, "my_find",1);
 *	.
 *	.
 *    mixed my_find(object searcher, string what)
 *    {
 *        return "You find that there is no exit in this room.\n";
 *    }
 */

static mapping gSearch_items = ([ ]);

/*
 * Function:	add_search
 * Arguments:	ids: A string or a list of strings to search for
 *		     NOTE: The ids can only be searched if they either
 *			   start with 'here' or are an add_item at
 *			   the same time!!!
 *		stime: The time the search takes.
 *		effect: This can be one of several things:
 *			- a filename (must start with '/'!) of an object
 *			  to clone and move to the room (to the player
 *			  if switch < 0).
 *			- a functionname (this is indicated with switch
 *                        != 0) with a function to call when the search
 *			  was successful. The function will get the searcher
 *			  and the search arg passed as arguments. Note that
 *                        moving the found object to the player or room must
 *                        be done inside the function!
 *			- a normal string. This is returned. Switch must
 *                        be 0 or not present.
 *			  NOTE: The string CAN'T be a VBFC.
 *		switch: (See above) an integer indicateing the number of
 *			things that can be found per reset or allows
 *                      to distingguish between function call and string.
 * Description:	Add the ids to the room so they can be searched.
 *		When they are searched successfully, do whatever the effect
 *		is set to. Else return the default message.
 */
varargs nomask public void
add_search(mixed ids, int stime, mixed effect, int sw = 0)
{
    int size, i = -1;
    mixed tmp;

    if (stringp(ids))
	gSearch_items += ([ids : ({ stime, effect, sw, sw }) ]);
    else
	if (pointerp(ids))
	{
	    tmp = ({ stime, effect, sw, sw });
	    size = sizeof(ids);

	    while (++i < size)
		gSearch_items += ([ ids[i] : tmp ]);
	}
}

query_search_items()
{
    return gSearch_items;
}

void
reset_search_room()
{
    int size, i = -1;
    mixed idx = m_indexes(gSearch_items);

    size = sizeof(idx);

    while (++i < size)
        gSearch_items[idx[i]][2] = gSearch_items[idx[i]][3];
}

/*
 * Function:	search_object
 * Description:	Someone tries to search this object
 * Arguments:	str - The string searched
 */
nomask public void
search_object(string str)
{
    mixed this_search = gSearch_items[str];

    if (this_search && pointerp(this_search))
    {
	add_prop(OBJ_I_SEARCH_TIME, this_search[0]);
	add_prop(OBJ_S_SEARCH_FUN, "krynn_search_fun");
    }
    ::search_object(str);
}

mixed
herb_search(object searcher, string what)
{
    return 0;
}

/*
 * Function:	krynn_search_fun
 * Description:	This function is called from object.c to handle
 *		a search.
 */
nomask public mixed
krynn_search_fun(object searcher, string what)
{
    mixed this_search = gSearch_items[what];
    string effect, str;
    mixed sw;
    object ob;

    /* Remove the prop again so it isn't some obscure value for a normal search */
    remove_prop(OBJ_I_SEARCH_TIME);

    if (!this_search || !pointerp(this_search))
	return herb_search(searcher, what);

    effect = this_search[1];
    sw = this_search[2];

    if (!effect || !stringp(effect))
	return herb_search(searcher, what);

    if (effect[0..0] == "/")
    {
	if (sw > 0)
	{
	    this_search[2]--;

	    ob = clone_object(effect);
	    str = LANG_ASHORT(ob);
	    ob->move(this_object());

	    str = "You find " + str + "!\n";
	    tell_room(this_object(), QCTNAME(searcher) + " finds something.\n",
		      searcher);
	}
	else if (sw < 0)
	{
	    this_search[2]++;

	    ob = clone_object(effect);
	    str = LANG_ASHORT(ob);
	    if (!ob->move(searcher))
	    {
		str = "You find " + str + " and pick it up!\n";
		tell_room(this_object(), QCTNAME(searcher) + " finds something and " +
			  "picks it up.\n", searcher);
	    }
	    else
	    {
		ob->move(E(searcher),1);
		str = "You find " + str + " but are unable to pick it up!\n";
		tell_room(this_object(), QCTNAME(searcher) + " finds somethings.\n",
			  searcher);
	    }
	}
	if (str)
	    return str;

	return herb_search(searcher, what);
    }
    if (sw)
	sw = call_other(this_object(), effect, searcher, what);
    else
	sw = effect;

    if (sw)
	return sw;

    return herb_search(searcher, what);
}
