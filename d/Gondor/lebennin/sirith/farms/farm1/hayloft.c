/*
 * /d/Gondor/lebennin/sirith/farms/farm1/loft.c
 * hayloft in barn of large farmstead in southern lebennin
 *
 * Copyright (C) 1997 by Nancy L. Mintz (Gnadnar)
 *
 * a pitchfork is hidden in the hay.
 */

#pragma strict_types

#include <stdproperties.h>	/* for OBJ_S_SEARCH_FUN, etc	*/
#include <ss_types.h>			/* for SS_AWARENESS	*/
#include "/d/Gondor/defs.h"
#include "../defs.h"			

inherit "/d/Gondor/lebennin/sirith/room";

static int	Pitchfork_here = 1;

public void	create_sirith();
public void	reset_room();
public void	init();
public int	climb(string arg);
public string	do_search(object tp, string arg);


/*
 * Function name:	create_sirith
 * Description	:	set up room
 */
public void
create_sirith()
{
    set_short("a hayloft");
    set_long(BSN("A hayloft. Stacks of hay fill the loft and threaten to "+
	"spill through the opening in the center of the floor. "+
	"There is very little room to move about."));

    set_no_exit_msg( ({ "north", "northeast", "east", "southeast",
	"south", "southwest", "west", "northwest", "up" }),
	BSN("There is not enough room for you to move about.") );

    add_prop(ROOM_I_LIGHT, 1);
    add_prop(ROOM_I_INSIDE, 1);

    add_prop(OBJ_S_SEARCH_FUN, "do_search");
    add_prop(OBJ_I_SEARCH_TIME, 3);

    add_item( ({ "loft", "hayloft" }), long);
    add_item( ({ "floor" }),
	BSN("Only the opening in the center of the floor is visible; "+
	    "the rest of the floor is covered with hay."));
    add_item( ({ "square opening", "opening" }),
	BSN("The opening is about three feet square; below it, "+
	    "a ladder leads down."));
    add_item( ({ "ladder" }),
	BSN("The ladder is crude, but functional."));
    add_item( ({ "ceiling" }),
	BSN("The sloping ceiling is just above your head."));
    add_item( ({ "hay", "stacks", "stack" }),
	BSN("Stacks of golden, sweet-smelling hay fill the loft."));
    
    /* not going to bother with <direction> wall, since the room
     * doesn't call attention to any wall in particular
     */
    add_item( ({ "wall", "walls", "plank", "planks" }),
	BSN("The walls are wide grey planks."));

    /* other people in the room really should see TP sneeze. RSN i'm
     * gonna roll my own add_cmd_item ...
     */
    add_cmd_item( ({ "hay", "stacks", "stack" }),
	({ "smell", "sniff" }),
	BSN("The hay tickles your nose, causing you to sneeze violently."));

    add_cmd_item( ({ "hay", "stacks", "stack" }),
	({ "climb" }),
	BSN("The hay is too slippery to climb."));

} /* create sirith */


/*
 * Function name:	reset_room
 * Description	:	replenish pitchfork
 */
public void
reset_room()
{
    ::reset_room();
    Pitchfork_here = 1;
} /* reset_room */


/*
 * Function name:	init
 * Description	:	add player verbs
 */
public void
init()
{
    ::init();
    add_action(climb, "climb");
    add_action(climb, "down");
} /* init */


/*
 * Function name:	climb
 * Description	:	let players climb down the ladder to the barn,
 * Arguments	:	string arg -- whatever the player typed
 * Return	:	1 if we recognize the arg, 0 if not
 */
public int
climb(string arg)
{
    string tmp;

    if (QVB == "down")
    {
	arg = "down";
    }
    if (strlen(arg))
    {
	/* don't accept "climb down down" :-)  */
	if (arg != "down" &&
	    sscanf(arg, "down %s", tmp) == 1 &&
	    tmp != "down")
	{
	    arg = tmp;
	}
	if (arg != "down" &&
	    arg != "pieces of wood" && 
	    arg != "ladder" &&
	    arg != "opening" &&
	    arg != "through opening")
	{
	    NFN0("Climb what?");
	}

	/* no skill checks for climbing down. they managed to get up
	 * here, so assume they'll make it down ok.
	 */
	write("You scramble down the crude ladder.\n");
	TP->move_living("down the ladder",
	    SIRITH_FARMS_DIR+"farm1/barn1");
	return 1;
    }
    NFN0("Climb what?");
} /* climb */


/*
 * Function name:	do_search
 * Description	:	handle searching the room & items
 * Arguments	:	object tp	this player
 *		:	string		whatever the player searched
 */
public string
do_search(object tp, string arg)
{
    object pfork;

    if (arg != "hay" &&
	arg != "stack" &&
	arg != "stacks")
    {
	/* a hint to give a target ... */
	return BSN("You poke around the hayloft, but find "+
		   "nothing interesting.");
    }

    if (Pitchfork_here &&
        TP->query_skill(SS_AWARENESS) >= (MIN_AWARE + random(RANDOM_AWARE)) &&
        objectp(pfork = clone_object(SIRITH_FARMS_DIR + "obj/pfork")))
    {
	Pitchfork_here = 0;
    	if (!pfork->move(tp))
	{
	    return "You find a pitchfork buried in the hay.\n";
	}

	/* else move to player failed ... drop it */
	pfork->move(TO);
	return "You find a pitchfork buried in the hay.\n"+
	       "Oops -- you dropped it.\n";
    }
    return BSN("You search the "+arg+
	       ", but do not find anything of interest.");
} /* do_search */
