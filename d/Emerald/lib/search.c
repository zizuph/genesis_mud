/* This module simplifies adding items that can be found by searching
 * a room.
 *
 * Example:
 * 
 * inherit "/d/Emerald/std/room";
 * inherit "/d/Emerald/lib/search";
 *
 * public void
 * create_emerald_room()
 * {
 *     ... misc configuration ...
 *     // Allow players to find an item when searching the trees or branches
 *     add_search(({ "trees", "branches" }), "/d/Emerald/obj/thing");
 * }
 *
 * public void
 * reset_room()
 * {
 *     // Only one item can be found per reset.
 *     reset_search();
 * }
 */

#include <language.h>
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>

static mapping gSearch_map = ([]);

/*
 * Function name: add_search
 * Description:   Add items which can be revealed by searching.
 * Arguments:     1. (mixed) The name(s) of the place(s) that can be searched
 *                2. (mixed) The item(s) which can be revealed when these
 *                           places are searched.
 *                3. (int)   The time the search will take
 *                4. (int)   The difficulty of the search, 0 - 100, 0 indicating
 *                           guaranteed success, 100 indicating guaranteed
 *                           failure.
 * Returns:       true if search items could be added
 */
public varargs int
add_search(mixed places, mixed items, int time = 5, int difficulty = 0)
{
    int i;

    if (stringp(places)) 
    {
	places = ({places});
    }
    else if (!pointerp(places))
    {
        return 0;
    }

    if (!pointerp(items))
    {
	items = ({items});
    }

    if (this_object()->query_prop(OBJ_S_SEARCH_FUN))
    {
	return 0;
    }

    this_object()->add_prop(OBJ_S_SEARCH_FUN, "search_fun");
    this_object()->add_prop(OBJ_I_SEARCH_TIME, time);

    for (i = 0; i < sizeof(places); i++)
    {    
        gSearch_map[places[i]] = ({ items, difficulty });
    }

    return 1;
}

/*
 * Function name: query_search_successful
 * Description:   Determine whether the searcher is successful in finding an
 *                item.  This can be redefined if you want to use a different
 *                routine.
 * Arguments:     1. (object) The searcher
 *                2. (int)    The difficulty of the search, 0 - 100
 * Returns:       true if the search is successful
 */
public int
query_search_successful(object searcher, int difficulty)
{
    // %70 awareness + %30 average of INT and WIS, capped at 200
    int search = searcher->query_skill(SS_AWARENESS) * 7 / 10;
  
    search += min(200,
        (searcher->query_stat(SS_INT) + searcher->query_stat(SS_WIS) / 2)) *
         3 / 20;

    return search > difficulty;
}

public string
search_fun(object searcher, string what)
{
    mixed *tmp, items, item;
    int difficulty;

    if (!present(searcher, this_object()))
    {
	return 0;
    }

    if (!what || !pointerp(tmp = gSearch_map[what]))
    {
	return 0;
    }

    if (this_object()->query_searched())
    {
	return 0;
    }

    if (!query_search_successful(searcher, difficulty))
    {
        return 0;
    }

    items = tmp[0];
    difficulty = tmp[1];

    setuid(); seteuid(getuid());

    // Check to see if a function pointer has been passed
    if (functionp(items))
    {
        if (!(items = items()))
	{
	    return 0;
	}
    }

    // If we have an array of items, choose randomly.  If it's just
    // one thing, that's our item.
    if (pointerp(items))
    {
        if (!sizeof(items))
        {
	    return 0;
        }

        item = items[random(sizeof(items))];
    }
    else
    {
        item = items;
    }

    if (!item)
    {
	return 0;
    }
    // I suppose we might want to use a function pointer to produce the item
    // itself.
    else if (functionp(item))
    {
        if (!(item = item()))
	{
            return 0;
	}
    }

    // At this point, we either have to have an object or the filename of an
    // object that can be cloned.
    if (!objectp(item) && !(item = clone_object(item)))
    {
        return 0;
    }

    this_object()->set_searched(1);
    if (item->move(searcher, 1))
    {
	item->move(environment(searcher), 1);
	tell_room(this_object(), QCTNAME(searcher) + " finds something and "+
	  "places it on the "+(this_object()->query_prop(ROOM_I_INSIDE) ? 
	    "floor" : "ground")+".\n", searcher);
	return "You find "+LANG_ASHORT(item)+", but are unable to carry it so "+
	"you place it on the "+(this_object()->query_prop(ROOM_I_INSIDE) ? 
	  "floor" : "ground") + ".\n";
    }

    tell_room(this_object(), QCTNAME(searcher) + " finds something "+
      "and quickly picks it up.\n",searcher);
    return "You find "+LANG_ASHORT(item)+" and quickly pick it up.\n";
}

mixed *
query_search_items(string what)
{
    return gSearch_map[what];
}

string *
query_search_places()
{
    return m_indices(gSearch_map);
}

void
reset_search()
{
    this_object()->set_searched(0);
}
