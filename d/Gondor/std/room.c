/*
 *	/d/Gondor/std/room.c
 *
 *	/std/room.c with a few functions added
 *
 *	Copyright (C) Christian Markus 1995
 *
 *	Olorin, August 1995
 *
 *	Revision history:
 *         Added default values for ROOM_I_SUNLIGHT against vampires.
 *         - Elessar, Apr. 16th 1997
 *         Added function try_item() for use in master files.
 *         - Gorboth, August 21st 1997
 *         Changed type of clone_npcs from void to int.
 *         - Olorin, 27-Aug-1997
 *	   Added set_no_exit_msg() and Exa_arg.
 *	   - Gnadnar, 15-Jan-1998 -> added to mudlib /Mercade
 */
#pragma strict_types

inherit "/std/room.c";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/sys/sunlight.h"
#include "/d/Gondor/common/lib/time.h"

public void	check_sunlight();

static string	Exa_arg;	/* to know which item player looked at	*/

/*
 * Function name: create_gondor
 * Description:   creator for rooms in Gondor
 */
public void
create_gondor()
{
}

/*
 * Function name: create_room
 * Description:   room creator
 */
nomask void
create_room()
{
    create_gondor();

    if (!query_prop(ROOM_I_INSIDE) && !query_prop_setting("_room_i_sunlight"))
        add_prop("_room_i_sunlight", check_sunlight);
}

/*
 * Function name: clone_npc
 * Description:   Clone one npc into this room and arm it.
 * Arguments:     npc  - the object pointer to the npc.
 *                file - the file name of the npc.
 *                restrain_path (optional) -
 *                       set the monster restrain path.
 *                setup (optional) - function to be 
 *                called in the npc before arm_me is called.
 * Returns:       the object pointer to the npc.
 * Usage:
 *
 * inherit "/d/Gondor/std/room.c";
 *
 * #include "/d/Gondor/defs.h"
 *
 * #define NPC_FILE	("/d/Gondor/common/npc/orc")
 *
 * // Global variables
 * object  Npc;
 * 
 * void
 * reset_room()
 * {
 *     Npc = clone_npc(Npc, NPC_FILE);
 * }
 * 
 */
public varargs object
clone_npc(object npc, string file, mixed restrain_path, function setup)
{
    if (objectp(npc))
        return npc;

    npc = clone_object(file);
    if (functionp(setup))
	setup();
    npc->arm_me();
    if (stringp(restrain_path))
	restrain_path = ({ restrain_path });
    if (pointerp(restrain_path) && sizeof(restrain_path))
	npc->set_restrain_path(restrain_path);
    npc->move_living("from the void", TO);

    return npc;
}

/*
 * Function name: clone_npcs
 * Description:   Clone more than one npc into this room and arm it.
 * Arguments:     npcs  - the array of object pointers to the npcs.
 *                file  - the file name of the npc.
 *                delay - how long until the next npc is cloned,
 *                        if <= 0.0, no set_alarm
 *                c     - counter, how many times has clone_npcs been
 *                        called since reset? 
 *                restrain_path (optional) -
 *                      - set the monster restrain path.
 *                setup (optional) - function to be called before arm_me
 * Returns:       -1 if delay > 0 and a npc was cloned,
 *                 0 if no npc was cloned,
 *                 n if delay == o and n npcs were cloned.
 * Usage:
 *
 * inherit "/d/Gondor/std/room.c";
 *
 * #include "/d/Gondor/defs.h"
 *
 * #define NPC_FILE	("/d/Gondor/common/npc/orc")
 *
 * // Global variables
 * object *Npcs = allocate(3 + random(3));
 * 
 * void
 * reset_room()
 * {
 *     set_alarm(4.0, 0.0, &clone_npcs(Npcs, NPC_FILE, 10.0));
 * }
 *
 */
public varargs int
clone_npcs(object *npcs, string file, float delay, mixed restrain_path, int c = 0, function setup = 0)
{
    int     i, s,
            count = 0;

    for (i = c, s = sizeof(npcs); i < s; i++)
    {
        if (!objectp(npcs[i]))
        {
	    count++;
	    if (restrain_path && functionp(setup))
		npcs[i] = clone_npc(npcs[i], file, restrain_path, setup);
	    else if (restrain_path)
		npcs[i] = clone_npc(npcs[i], file, restrain_path);
	    else if (functionp(setup))
		npcs[i] = clone_npc(npcs[i], file, 0, setup);
	    else
		npcs[i] = clone_npc(npcs[i], file);
	    if ((delay > 0.0) && (++c < s))
	    {
		set_alarm(delay + delay * rnd(), 0.0, 
			  &clone_npcs(npcs, file, delay, restrain_path, c, setup));
		return -1;
	    }
        }
    }

    return count;
}

/*
 * Function name: check_sunlight
 * Description:   Return the sunlight level in the room (default)
 *                The value of the sunlight level determines the rate of
 *                herb growth and the panic level of orcs and trolls
 *                (save of uruks)
 * Returns:       the sunlight level in the room (values from 0 to 100)
 */
public int
check_sunlight()
{
    if (query_prop(ROOM_I_INSIDE))
        return 0;

    switch (tod())
    {
    case "night":
        return SUNLIGHT_SHADOWY;
        break;
    case "early morning":
    case "evening":
        return SUNLIGHT_DIM;
        break;
    default:
    case "morning":
    case "afternoon":
        return SUNLIGHT_NORMAL;
        break;
    case "noon":
        return SUNLIGHT_BRIGHT;
        break;
    }
}

/*
 * Function name:	try_item
 * Description	:	checks to see if an item already exists
 *                	within a given object, and if it does not, it then
 *                	adds it as add_item() would.
 * Arguments	:	mixed names --  string or array of strings, the
 *					item name(s).
 *			mixed desc -- string or function, the description.
 * Returns	:	int -- the number of items added
 */
public int
try_item(mixed names, mixed desc)
{
    int		i;
    string	*exists;

    if (pointerp(names)) 
    { 
	exists = ({});
        for (i = 0; i < sizeof(names); i++) 
	{
            if (item_id(names[i])) 
	    {
		exists += ({ names[i] });
	    }
	}
	names -= exists;
	if ((i = sizeof(names)))
	{
	    add_item(names, desc);
	}
    } 
    else if (!TO->item_id(names))
    {
    	add_item(names, desc);
	i = 1;
    }
    return i;	/* # of items added */
}

/*
 * Function name:	long
 * Description  :	look at room or item
 * Arguments    :	name of item, or 0
 * Returns      :	string holding description
 *
 * If user did "exa", arg to long() will be whatever they tried to
 * examine. Intercept long() so we can remember the arg for use 
 * by VBFC and so on.
 */
varargs public mixed
long(string str)
{
    Exa_arg = str;
    return ::long(str);
}

public void	set_exa_arg(string arg) { Exa_arg = arg; }
public string	query_exa_arg()		{ return Exa_arg; }
