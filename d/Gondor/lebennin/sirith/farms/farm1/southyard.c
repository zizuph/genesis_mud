/*
 * /d/Gondor/lebennin/sirith/farms/farm1/southyard.c
 * south yard of large farmstead in southern lebennin
 *
 * Copyright (C) 1997 by Nancy L. Mintz (Gnadnar)
 * Finwe,May 2019: Removed hidden exits
 *
 */

#pragma strict_types

#include <filter_funs.h>		/* for FILTER_LIVE	*/
#include <composite.h>			/* for COMPOSITE_LIVE	*/
#include "/d/Gondor/defs.h"
#include "../defs.h"			

inherit "/d/Gondor/lebennin/sirith/farms/outdoors";

#define	PEN	(SIRITH_FARMS_DIR+"farm1/pigsty")

public void	create_outdoors();
public void	init();
public int	climb_fence(string arg);
public string	look_pen();


/*
 * Function name:	create_oudoors
 * Description	:	set up room
 */
public void
create_outdoors()
{
    set_areatype("farmyard");
    set_short("a farmyard in southern Lebennin");
    set_extraline("A fence runs between the hedge and the turf bank, "+
	"and a sturdy gate leads south into a muddy enclosure.");

    add_exit("eastyard", "north", 0, 2);
    add_exit("pigsty", "south", 0, 2);
    set_no_exit_msg( ({ "northeast", "east", "southeast",
	"southwest", "west", "northwest", "up", "down" }),
	BSN("You stroll around the farmyard.") );

    set_door(SIRITH_FARMS_DIR + "obj/f1_pigsty_gate1");
    set_climbdest(SIRITH_FARMS_DIR + "farm1/pigsty");

    add_item( ({ "farmyard", "farm", "yard" }),
	BSN("A tidy farmyard, enclosed by a turf bank."));
    add_item( "hedge",
	BSN("The tall hedge blocks your view to the west."));
    add_item( ({ "bank", "turf", "turf bank" }),
	BSN("The bank is formed of blocks of turf. It circles the "+
	    "entire farmyard."));
    add_item( ({ "ground", "dirt", "mud" }),
	BSN("The ground outside the pen is bare, packed dirt; "+
	    "inside the pen, it is deep mud."));
    add_item( ({ "fence", "fencing" }),
	BSN("The fence around the muddy enclosure is quite sturdy.") );
    add_item( ({ "muddy enclosure", "pen", "enclosure", "area" }),
	look_pen);
    add_item( ({ "shelter" }),
	BSN("At the rear of the pen is covered shelter, but you cannot "+
	    "see it clearly from here."));

    /* dead simple .. even a pig can sometimes open it :-) */
    add_item( ({ "latch", "prong", "prongs", "fencepost", "post" }),
	BSN("The latch is simply two wooden prongs that swivel to "+
	    "fall one on either side of the fencepost."));

    /* force the sty to load now. otherwise, if a player causes it
     * to load by examining the pen while in this room, it looks 
     * odd:
     *   > exa pen
     *   A huge pig ambles into view.
     *   The huge pig walks to the gate and nudges the latch up with her snout.
     *   The huge pig ambles south.
     *   The pen is simply a muddy area, enclosed by a sturdy fence. There 
     *   is a shelter of some kind at the back.
     *   A huge pig is standing in the pen.
     *   > 
     */
    PIGSTY->short();
} /* create_outdoors */


/*
 * Function name:	init
 * Description	:	add player verbs
 */
public void
init()
{
    ::init();
    add_action(climb_fence, "climb");
    add_action(climb_fence, "jump");
} /* init */


/*
 * Function name:	climb_fence
 * Description	:	let players climb the fence
 * Arguments	:	string arg -- whatever the player typed
 * Return	:	1 if we recognize the arg, 0 if not
 */
public int
climb_fence(string arg)
{
    object gate;

    if (arg == "fence" ||
	arg == "fencing")
    {
	set_dircmd("fence");
	write(BSN("You scramble over the fence."));
	TP->move_living("over the fence",
	    SIRITH_FARMS_DIR+"farm1/pigsty");
	return 1;
    }
    else if (arg == "gate" ||
	     arg == "wooden gate" ||
	     arg ==  "fence gate")
    {
	if (objectp(gate = present(SIRITH_DOOR)) &&
	    gate->query_open())
	{
	    write(CAP(QVB)+"ing an open gate is pointless.\n");
	}
	else
	{
	    set_dircmd("gate");
	    write("You scramble over the gate.\n");
	    TP->move_living("over the gate",
	        SIRITH_FARMS_DIR+"farm1/pigsty");
	}
	return 1;
    }
    return 0;
} /* climb_fence */


/*
 * Function name:	look_pen
 * Description	:	describe pen, including any livings present
 * Returns	:	string description
 */
public string
look_pen()
{
    object	*in_pen;
    string	desc;
    int		n;

    PEN->short();
    in_pen = FILTER_LIVE(all_inventory(find_object(PEN)));

    desc = BSN("The pen is simply a muddy area, enclosed by "+
	    "a sturdy fence. There is a shelter of some kind at "+
	    "the back.");

    if ((n = sizeof(in_pen)) == 1)
    {
	desc +=  BSN(in_pen[0]->query_Art_name(TP)+
	    " is standing in the pen.");
    }
    else if (n > 1)
    {
	desc += BSN(capitalize(COMPOSITE_LIVE(in_pen))+
	    " are standing in the pen.");
    }
    return desc;
} /* look_pen */
