/*
 * information_master.c
 *
 * This object is a master object for the domain which connects the
 * different information modules for the different regions.
 * Basically it just contains a mapping of all the different
 * places with them, and the filepaths to their info modules.
 *
 */
#pragma strict_types
#pragma no_clone

#include <math.h>
#include <std.h>
#include "/d/Khalakhor/sys/defs.h"
#include "gks.h"

inherit "/std/object";

mapping modules;

/* PROTOTYPES */
public void create_object();
public int *get_my_local_coords(object ob);
public int *get_my_global_coords(object ob);
public string resolve_my_location(int *coords);
public object resolve_other_location(string loc, object old, int *myglobal);
public string composite_options(string *str);
public int resolve_distance_value(int *coords1, int *coords2);
public string resolve_distance_string(int hyp, string mode);
public string resolve_direction(int delta_x, int delta_y);
public string get_response(string location, object caller, int *myglobal,
  int *mylocal, string info_string);

public void
create_object()
{
    modules = ([
      "Port_Macdunn": "/d/Khalakhor/se_speir/port/information",
      "Tabor_Sogh": "/d/Khalakhor/se_speir/claryn/tabor/information",
      "Clach_Dun": "/d/Khalakhor/n_speir/clachdun/information",
    ]);
}

public mixed
query_modules()
{
    return modules + ([]);
}

/*
 * Function name: get_my_local_coords
 * Description  : Gets the local coords of the npc requesting
 *                information.
 * Arguments    : ob - The npc wanting information.
 * Returns      : Array of two ints, the x-y coords. An
 *                empty array if no coords are available.
 */
public int *
get_my_local_coords(object ob)
{
    if (!environment(ob) ||
      !(environment(ob)->query_local_coords()))
	return ({});
    return environment(ob)->query_local_coords();
}

/*
 * Function name: get_my_global_coords
 * Description  : Gets the global coords of the npc requesting
 *                information.
 * Arguments    : ob - The npc wanting information.
 * Returns      : Array of two ints, the x-y coords. An
 *                empty array if no coords are available.
 */
public int *
get_my_global_coords(object ob)
{
    if (!environment(ob) ||
      !(environment(ob)->query_global_coords()))
	return ({});
    return environment(ob)->query_global_coords();
}

/*
 * Function name: resolve_my_location
 * Description  : This function takes the global coords
 *                of the calling npc, and figures out
 *                which info module to use for its
 *                immediate location.
 * Arguments    : Array of two integers, the x-y global
 *                coords of the npc's location.
 * Returns      : The 'modules' mapping index which contains
 *                the module for the specified location, or
 *                an empty string if no module is available
 *                for the current location.
 */
public string
resolve_my_location(int *coords)
{
    int i,
    *tcoords;
    string index;

    setuid();
    reset_euid();

    for (i = 0; i < m_sizeof(modules); i++)
    {
	index = m_indexes(modules)[i];
	tcoords = modules[index]->query_global_coords();
	if (tcoords[0] == coords[0] &&
	  tcoords[1] == coords[1])
	    return index;
    }

    return "";
}

/*
 * Function name: resolve_other_location
 * Description  : Determines which information module we should use
 *                to provide the information asked of us. This is
 *                how an npc in one village could direct a player
 *                to something in another village.
 * Arguments    :
 * Returns      : Object pointer to the relevant info module.
 */
public object
resolve_other_location(string loc, object old, int *myglobal)
{
    mixed temparr;
    object *infoarr;
    mapping dist;
    int i,
    tempd;

    reset_euid();

    /* First get object pointers to all info modules. */
    infoarr = m_values(modules)->get_this_object();
    infoarr -= ({old});

    /* Next we filter out all modules which do not identify */
    /* the given location. */
    infoarr = filter(infoarr, &->match_location(loc));

    if (!sizeof(infoarr))
	return 0;

    /* Now we have an array of modules that define coords for */
    /* the desired location. This is where things get nasty, */
    /* as we have to decide which is closest. */

    /* Get an array of the global coords of all remaining mods. */
    temparr = infoarr->query_global_coords();
    /* Make the previous array into an array of distances. */
    temparr = map(temparr, &resolve_distance_value(myglobal,));
    /* Make a mapping of distances and modules. */ 
    dist = mkmapping(temparr, infoarr);
    /* Use sort array to put the shortest distance at the 0'th */
    /* element. */
    temparr = sort_array(temparr);
    /* Use the 0'th element to return the closest module from */
    /* the dist mapping. */
    return dist[temparr[0]];
}

/*
 * Function name: composite_options
 * Description  : Takes an array of words and generates them into
 *                a formatted list of options. I.e. it takes
 *                ({"a","b","c"}) and makes "a, b or c".
 * Arguments    : str - An array of strings.
 * Returns      : A single string.
 */
public string
composite_options(string *str)
{
    if (!sizeof(str))
	return "";

    if (sizeof(str) == 1)
	return str[0];

    if (sizeof(str) == 2)
	return implode(str, " or ");

    return implode(str[0..sizeof(str) - 2], ", ") +
    " or " + str[sizeof(str) - 1];
}

/*
 * Function name: resolve_distance_value
 * Description  : Returns a distance between two coords.
 * Arguments    : coords1 - First set of x-y coords as array of 2 ints.
 *                coords2 - Second set of x-y coords as array of 2.
 * Returns      : distance as an int.
 */
public int
resolve_distance_value(int *coords1, int *coords2)
{
    int delta_x,
    delta_y;
    delta_x = coords1[0] - coords2[0];
    delta_y = coords1[1] - coords2[1];
    return SQUARE_ROOT((delta_x * delta_x) + (delta_y * delta_y));
}

/*
 * Function name: resolve_distance_string
 * Description  : Takes an integer and turns it into a string
 *                describing the relative distance, varying with
 *                "local" and "global" coords.
 * Arguments    : hyp - The distance between two points as an int.
 *                mode - "local" or "global" distance.
 * Returns      : String describing the distance.
 */
public string
resolve_distance_string(int hyp, string mode)
{
    if (mode == "local")
    {
	if (hyp <= 1)
	    return "immediately";
	if (hyp <= 3)
	    return "a quick walk";
	if (hyp <= 6)
	    return "a short walk";
	if (hyp <= 10)
	    return "a fair walk";
	if (hyp <= 15)
	    return "a long walk";
	if (hyp <= 21)
	    return "a very long walk";
	return "an exhaustive walk";
    }
    else if (mode == "global")
    {
	if (hyp <= 1)
	    return "immediately";
	if (hyp <= 3)
	    return "a brief journey";
	if (hyp <= 6)
	    return "a short journey";
	if (hyp <= 10)
	    return "a fair journey";
	if (hyp <= 15)
	    return "a long journey";
	if (hyp <= 21)
	    return "an exhaustive journey";
    }

    return "an unknown distance";
}

/*
 * Function name: resolve_direction
 * Description  : Translates differences in x and y coord points
 *                to one of the eight cardinal directions.
 * Arguments    : delta_x - Integer difference between points
 *                          on the x-axis (target x - local x)
 *                delta_y - Same as delta_x, only on the y axis.
 * Returns      : A string describing the direction the target
 *                lies in from the local. I.e. 'north', 'northeast',
 *                'southwest', etc.
 */
public string
resolve_direction(int delta_x, int delta_y)
{
    float slope;
    string temp,
    quad;

    if (!delta_x)
    {
	if (delta_y > 0)
	    return "south";
	return "north";
    }

    if (!delta_y)
    {
	if (delta_x > 0)
	    return "east";
	return "west";
    }

    if (delta_x > 0 && delta_y < 0)
	quad = "northeast";
    else if (delta_x < 0 && delta_y < 0)
	quad = "northwest";
    else if (delta_x < 0 && delta_y > 0)
	quad = "southwest";
    else
	quad = "southeast";

    slope = itof(delta_y) / itof(delta_x);

    if (quad == "northeast")
    {
	if (slope > -0.5)
	    return "east";
	if (slope > -2.0)
	    return "northeast";
	return "north";
    }
    if (quad == "northwest")
    {
	if (slope > 2.0)
	    return "north";
	if (slope > 0.5)
	    return "northwest";
	return "west";
    }
    if (quad == "southwest")
    {
	if (slope > -0.5)
	    return "west";
	if (slope > -2.0)
	    return "southwest";
	return "south";
    }
    if (slope > 2.0)
	return "south";
    if (slope > 0.5)
	return "southeast";
    return "east";
}

/*
 * Function name: get_response
 * Description  : Generates a response for an npc to give via
 *                command("say " + response); when asked about
 *                the location of certain places.
 * Arguments    : location - String which is the name of the place
 *                           a player is looking for. I.e. 'pub'.
 *                caller - Object pointer to the npc who is to
 *                         respond.
 * Returns      : An output string as described.
 */
public string
get_response(string location, object caller, int *myglobal,
  int *mylocal, string info_string)
{
    int *oglobal,
    *olocal,
    dist,
    x_diff,
    y_diff,
    other_global_used;
    string temps,
    *tempsarr,
    direction,
    distance;
    object info_object;

    /* Failure response if no location specified. */
    if (!location || !strlen(location))
	return "Where is what?";

    /* Next we'll strip off things like 'the' and 'an' */
    parse_command(location, TP, "[the] [an] [a] %s", location);

    /* If the npc is in a room without global coords set, */
    /* then he's not likely to know his own location let */
    /* alone where anything else is. */
    if (!sizeof(myglobal))
	return "I'm not even sure where I am, let alone "+
	"where anything else is.";

    /* Next see if the npc is in an area that has an info */
    /* module connected to it. If not then no worries, but */
    /* if we are in one it could save time when looking for */
    /* the location later. */
    if (strlen(info_string))
	info_object = modules[info_string]->get_this_object();

    /* Now we have global coords for the calling npc, and */
    /* the information module if one is used for the area */
    /* the npc is in. The possibility exists that a location */
    /* name is duplicated in some info modules (for example, */
    /* there could be two or three different pubs in the */
    /* same village). However, an npc will only mention */
    /* this if they are in the area controlled by that module. */
    /* They won't differentiate if the same thing happens */
    /* in another area. So, we'll make a check here to see */
    /* if any of these duplicates exist if the npc is in */
    /* an area controlled by an info module. */
    if (info_object && 
      (sizeof(tempsarr = info_object->test_for_options(location))))
    {
	return "Hmm, do you mean the " +
	composite_options(tempsarr) + "?";
    }

    /* Ok, by this point, one of two things has happened. One is */
    /* that the npc isn't in an area controlled by an info module, */
    /* the other is that he _is_ in an area controlled, and the */
    /* specified location is not a duplicate. So, if the first */
    /* situation is the case, or if the second is the case but */
    /* 'location' isn't defined by it, we'll have to resolve out */
    /* a new info module from those available. If that doesn't */
    /* find a location, the npc gives up and confesses his */
    /* ignorance. */
    if (!info_object || 
      !sizeof(olocal = info_object->resolve_coords(location)))
    {
	info_object = resolve_other_location(location,
	  info_object, myglobal);
	other_global_used = 1;
	if (!info_object)
	    return "Hmm, don't know where that'd be, sorry.";
    }

    /* We already have the npc's global coords, here we get */
    /* the npc's local coords, and the location's global and */
    /* local coords. */
    oglobal = info_object->query_global_coords();
    olocal = info_object->resolve_coords(location);

    /* Ok, now we have the global and local coords for both the */
    /* npc and the place of interest. The rest is just formatting. */

    /* If global coords are the same, (that is the npc is in the */
    /* area that it found 'location' in), then the result is */
    /* based on local coords. */
    if (myglobal[0] == oglobal[0] && myglobal[1] == oglobal[1])
    {
	/* If local coords of 'location' are the same as the */
	/* npc's, then the npc is standing in 'location'. */
	if (mylocal[0] == olocal[0] && mylocal[1] == olocal[1])
	    return "Sure I know where it is, right here!";
	x_diff = olocal[0] - mylocal[0];
	y_diff = olocal[1] - mylocal[1];
	dist = SQUARE_ROOT((x_diff * x_diff) + (y_diff * y_diff));
	distance = resolve_distance_string(dist, "local");
	direction = resolve_direction(x_diff, y_diff);
    }
    else
    {
	x_diff = oglobal[0] - myglobal[0];
	y_diff = oglobal[1] - myglobal[1];
	dist = SQUARE_ROOT((x_diff * x_diff) + (y_diff * y_diff));
	distance = resolve_distance_string(dist, "global");
	direction = resolve_direction(x_diff, y_diff);
    }

    if (other_global_used)
	return "You're looking for the " + location + "? " +
	"I think the nearest one is " + distance + 
	" to the " + direction + ", in " +
	info_object->query_area_name() + ".";
    return "You're looking for the " + location + "? It's " +
    distance + " to the " + direction + " from here.";
}

