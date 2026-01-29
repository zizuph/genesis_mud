/*
 * information_base.c
 *
 * The information module defines different mappings:
 *
 * options - This mapping is used for multiple options of
 *           a landmark type, i.e. if there are more than one
 *           shop in a village. 'shop' is the mapping index,
 *           and the different shop's names are the values in
 *           an array.
 * aliases - This mapping is used for landmarks which may be
 *           referred to with different names. A shop could
 *           also be referred to as a store, for example. The
 *           values of this mapping are arrays of alternate
 *           placenames for a single place. The index is the
 *           'default' name for that location.
 * coords -  This mapping contains local coordinates for all
 *           of the major landmarks in the village. The coords
 *           are array values, the indexes are the default names
 *           which are resolved as the indexes of the aliases
 *           mapping.
 *
 * For example. A player asks an npc for a 'smith'. The npc finds
 * out that there's more than one from the options array, and
 * asks the player which smith he wants, the blacksmith or the
 * bladesmith. The player response with a request for the blacksmithy.
 * Blacksmithy is an alias for the default 'blacksmith', which the
 * npc then uses to obtain coords for the nearest blacksmith.
 *
 * Khail - August 1, 1997
 */
#pragma strict_types
#pragma no_clone
#include "/d/Khalakhor/sys/defs.h"
#include "gks.h"
inherit "/std/object";

mapping options,
        aliases,
        coords;
string area_name;
int *global_coords;

public void
create_info()
{
}

public nomask void
create_object()
{
    options = ([]);
    aliases = ([]);
    coords = ([]);
    area_name = "";
    global_coords = ({});
    create_info();
}

/*
 * Function name: query_global_coords
 * Description  : Returns the global coordinates for the area this
 *                module controls.
 * Arguments    : n/a
 * Returns      : An array of two integers, the global x-y coords.
 */
public int *
query_global_coords()
{
    return global_coords;
}

/*
 * Function name: test_for_options
 * Description  : Tests a given argument to see if there are
 *                more than one place it references.
 * Arguments    : str - The string to look for as having optional
 *                      references (i.e. if there's 2 places in
 *                      the city called 'shop').
 * Returns      : Always an array. If 'str' has options, it returns
 *                them as an array of strings. If no options, returns
 *                an empty array (Test for failure with if (!sizeof)).
 */
public string *
test_for_options(string str)
{
    if (options[str])
        return options[str];
    return ({});
}

/*
 * Function name: resolve_aliases
 * Description  : Filters through the aliases mapping to figure out
 *                if the given string is an alias for a default
 *                place name.
 * Arguments    : str - The string to test as an alias.
 * Returns      : If an alias found, the default name.
 *                If no alias found, an empty string.
 */
public string
resolve_aliases(string str)
{
    int i;
    string temp;

    if (member_array(str, m_indexes(aliases)) > -1)
        return str;

    for (i = 0; i < m_sizeof(aliases); i++)
    {
        temp = m_indexes(aliases)[i];
        if (member_array(str, aliases[temp]) > -1)
            return temp;
    }

    return "";
}

/*
 * Function name: resolve_coords
 * Description  : Attempts to return a set of local coords for
 *                a given location.
 * Arguments    : str - Place name to give coords for.
 * Returns      : An integer array of coords, or an empty array 
 *                if the specified place could not be located.
 */
public int *
resolve_coords(string str)
{
    str = resolve_aliases(str);
    if (!str || !strlen(str) || !coords[str])
        return ({});
    return coords[str];
}

/*
 * Function name: match_location
 * Description  : Returns true if this module describes
 *                a given location.
 * Arguments    : location - A string we are trying to 
 *                           test this info module for.
 *                           i.e. "shop".
 * Returns      : 0 - Location not defined.
 *                1 - Location defined.
 */
public int
match_location(string str)
{
    string temp;

  /* First we test for options. If the given string can */
  /* refer to different places (i.e. two different shops */
  /* in the same village) we'll just use the first one. */
    if (options[str])
        str = options[str][0];

  /* Finally, we'll return 'true' if a set of coords */
  /* exist. */
    if (sizeof(resolve_coords(str)))
        return 1;
    return 0;
}

public string
query_area_name()
{
    return area_name;
}
