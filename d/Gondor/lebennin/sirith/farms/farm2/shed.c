/*
 * /d/Gondor/lebennin/sirith/farms/farm2/shed.c
 * shed for small farmstead in southern lebennin
 *
 * Copyright (C) 1997 by Nancy L. Mintz (Gnadnar)
 *
 *
 */

#pragma strict_types

#include <stdproperties.h>		/* for OBJ_S_SEARCH_FUN	*/
#include <language.h>			/* for LANG_ADDART 	*/
#include <ss_types.h>			/* for SS_AWARENESS	*/
#include "/d/Gondor/defs.h"
#include "../defs.h"			

inherit "/d/Gondor/lebennin/sirith/room";

/* provide a sack ... a valued and scarce item, if i recall my newbie
 * days correctly. also provide a rope as a nice red herring to induce
 * players to waste time trying to tie the pig :-)
 */
static int	Rope_here = 1;
static int	Sack_here = 1;

public void	create_sirith();
public void	reset_room();
public string	do_search(object tp, string arg);


/*
 * Function name:	create_sirith
 * Description	:	set up room
 */
public void
create_sirith()
{
    set_short("a small shed");
    set_long(BSN("A small shed. The detritus of a working farm lies "+
	"piled against the walls."));

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 1);	/* shed has no door */

    add_exit("westyard", "east", 0, 2);
    set_no_exit_msg( ({ "north", "northeast", "southeast",
	"south", "southwest", "west", "northwest", "up", "down" }),
	BSN("You wander around the shed.") );

    add_prop(OBJ_S_SEARCH_FUN, "do_search");
    add_prop(OBJ_I_SEARCH_TIME, 3);

    add_item( ({ "shed" }), long);
    add_item( ({ "ground", "floor", "wall", "walls" }),
	BSN("The floor and walls are largely obscured by the piles "+
	    "of discarded objects."));
    add_item( ({ "ceiling", "plank", "planks", "roof" }),
	BSN("The ceiling is just the underside of the shed roof ... "+
	    "bare grey planks."));
    add_item( ({ "detritus", "pile", "piles", "discarded objects",
		 "objects", "junk", "odds", "ends", "odds and ends" }),
	BSN("Rusty tools and farm implements, scraps of wood, tattered "+
	    "sacking, odd bits of rope and twine, dirty rags and other "+
	    "such odds and ends are piled around the shed."));
    add_item( ({ "rusty tool", "rusty tools", "implement", "implements",
		 "farm implement", "farm implements", "tool", "tools" }),
	BSN("Most are rusted and not fit for use"));
    add_item( ({ "scraps of wood", "wood", "scrap", "scraps", "kindling" }),
	BSN("The wood scraps would only be useful as kindling."));
    add_item( ({ "tattered sacking", "sacking", "sack", "sacks" }),
	BSN("The coarse sacking is torn and dirty."));
    add_item( ({ "rope", "ropes", "twine" }),
	BSN("The pieces of rope and twine are too short to be "+
	    "of much use."));
    add_item( ({ "dirty rag", "dirty rags", "rag", "rags" }),
	BSN("The rags are tattered pieces of dirty cloth."));
} /* create_sirith */


/*
 * Function name:	reset_room
 * Description	:	replenish rope, sack
 */
public void
reset_room()
{
    ::reset_room();
    Rope_here = 1;
    Sack_here = 1;
} /* reset_room */


/*
 * Function name:	do_search
 * Description	:	handle searching the room & items
 * Arguments	:	object tp	this player
 *		:	string		whatever the player searched
 *
 */
public string
do_search(object tp, string arg)
{
    object	obj;
    string	where,
		what;

    if (!strlen(arg))
    {
	return BSN("You poke around the shed, but find "+
	     "nothing of any obvious value.");
    }

    if (sscanf(arg, "%s for %s", where, what) != 2)
    {
	where = arg;
    }

    if (where == "here")
    {
	return BSN("You poke around the shed, but find "+
	     "nothing of any obvious value.");
    }

    /* they cannot search the ceiling */
    if (where == "ceiling" ||
	where ==  "plank" ||
	where ==  "planks" ||
        where ==  "roof") 
    {
	return BSN("You gaze at the "+where+" for some time, "+
	    "but don't see anything out of the ordinary.");
    }

    if (where == "wall" ||
	where == "walls" ||
	where == "floor")
    {
	where = "piles of junk obscuring the "+where;
	if (strlen(what))
	{
	    arg = where+" for "+what;
	}
	else
	{
	    arg = where;
	}
    }

    if ((!Rope_here &&
	 !Sack_here) ||
        TP->query_skill(SS_AWARENESS) < (MIN_AWARE + random(RANDOM_AWARE)))
    {
	return BSN("You search the "+arg+
	    ", but do not find anything of interest.");
    }

    if (!strlen(what))
    {
	if (!Sack_here ||
	    (Rope_here &&
	     !random(2)))
	{
	    Rope_here = 0;
	    obj = clone_object("/std/rope");
	    obj->set_long(BSN("The rope is fairly short and its ends are "+
		"beginning to unravel."));
	}
	else
	{
	    Sack_here = 0;
	    obj = clone_object(LEB_DIR+"obj/sack");
	}
    }
    else if (what == "rope")
    {
	if (!Rope_here)
	{
	    return BSN("You search the "+arg+
		", but do not find anything of interest.");
	}
	Rope_here = 0;
	obj = clone_object("/std/rope");
	obj->set_long(BSN("The rope is fairly short and its ends are "+
	    "beginning to unravel."));
        obj->add_prop(OBJ_I_VALUE, 10);
    }
    else if (what == "sack")
    {
	if (!Sack_here)
	{
	    return BSN("You search the "+arg+
		", but do not find anything of interest.");
	}
	Sack_here = 0;
	obj = clone_object(LEB_DIR+"obj/sack");
    }
		

    if (objectp(obj))
    {
	SAY(" finds "+LANG_ADDART(obj->short())+".");
    	if (!obj->move(tp))
	{
	    return BSN("Hidden in the "+where+", you find "+
	    	LANG_ADDART(obj->short())+".");
	}

	/* else move to player failed ... drop it */
	obj->move(TO);
	return BSN("Hidden in the "+where+", you find "+
	           LANG_ADDART(obj->short())+".")+
	       "Oops -- you dropped it.\n";
    }
    return BSN("You search the "+arg+
	", but do not find anything of interest.");
} /* do_search */
