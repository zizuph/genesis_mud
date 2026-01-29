/*
 * /d/Gondor/lebennin/sirith/farms/farm1/barn1.c
 * barn of large farmstead in southern lebennin
 *
 * Copyright (C) 1997 by Nancy L. Mintz (Gnadnar)
 *
 */

#pragma strict_types

#include <stdproperties.h>		/* for ROOM_I_LIGHT	*/
#include <filter_funs.h>		/* for FILTER_LIVE	*/
#include <composite.h>			/* for COMPOSITE_LIVE	*/
#include <ss_types.h>			/* for SS_CLIMB		*/
#include "/d/Gondor/defs.h"
#include "../defs.h"			

inherit "/d/Gondor/lebennin/sirith/room";

#define	PEN	(SIRITH_FARMS_DIR+"farm1/barn2")

public void	create_sirith();
public void	init();
public int	climb(string arg);
public string	look_pen();


/*
 * Function name:	create_sirith
 * Description	:	create the room
 */
public void
create_sirith()
{
    set_short("a large barn");

    set_long(BSN("A large barn. This end of the barn is open, "+
	"with a cobbled floor; the western end is partitioned off "+
	"into a livestock pen. A ladder is fastened "+
	"to the east wall below a square opening in the ceiling."));

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 1);

    add_exit("barn2", "west", 0, 2);
    add_exit("westyard", "south", 0, 2);
    set_no_exit_msg( ({ "north", "northeast", "east", "southeast",
	"southwest", "northwest", "down" }), 
	BSN("You wander around the barn, but do not find "+
	    "anything of interest.") );

    add_item( "barn", long);
    add_item( ({ "ceiling" }),
	BSN("The ceiling is high above your head. There is an "+
	    "opening in it near the east wall."));
    add_item( ({ "north wall", "west wall",
		 "south wall", "plank", "planks" }),
	BSN("The walls are wide grey planks."));
    add_item( ({ "wall", "walls", "east wall" }),
	BSN("The walls are wide grey planks. "+
	    "A ladder is fastened to the east wall."));
    add_item( ({ "ladder", "wood", "pieces of wood" }),
	BSN("The ladder is just short, thick pieces of wood that "+
	    "have been nailed to the east wall."));
    add_item( ({ "opening", "hole", "loft", "hayloft" }),
	BSN("The opening seems to lead into a hayloft, "+
	    "but you can't see much from here."));
    add_item( ({ "pen", "partition" }), look_pen);

    /* don't say "the cobbled floor appears to be used for threshing",
     * since we may want to make them figure that out for harvest quest
     */
    add_item( ({ "ground", "floor", "cobbles", "stones", "cobblestones",
    		 "cobble", "stone", "cobblestone", "straw", 
		 "straws", "wheat", "grains", "grain" }),
	BSN("Bits of straw are scattered about the cobblestone floor "+
	    "and a few grains of wheat are stuck in the crevices "+
	    "between the stones."));
} /* create_sirith */


/*
 * Function name:	init
 * Description	:	add player verbs
 */
public void
init()
{
    ::init();
    add_action(climb, "climb");
    add_action(climb, "up");
} /* init */


/*
 * Function name:	climb
 * Description	:	let players climb the ladder to the hayloft,
 * Arguments	:	string arg -- whatever the player typed
 * Return	:	1 if we recognize the arg, 0 if not
 *
 */
public int
climb(string arg)
{
    string tmp;
    int climbskill;

    if (QVB == "up")
    {
	arg = "up";
    }
    if (strlen(arg))
    {
	/* don't accept "climb up up" :-)  */
	if (arg != "up" &&
	    sscanf(arg, "up %s", tmp) == 1 &&
	    tmp != "up")
	{
	    arg = tmp;
	}
	if (arg != "ladder" &&
	    arg != "pieces of wood" &&
	    arg != "up" &&
	    arg != "east wall" &&
	    arg != "opening" &&
	    arg != "through opening")
	{
	    NFN0("Climb what?");
	}

	/* check for just a little climbing skill */
	if ((TP->query_skill(SS_CLIMB) + random(5)) >= 8)
	{
	    write("You scramble up the crude ladder.\n");
	    TP->add_fatigue(-2);
	    TP->move_living("up the ladder",
		SIRITH_FARMS_DIR+"farm1/hayloft");
	    return 1;
	}

	write(BSN("You try to ascend the crude ladder, "+
	    "but you aren't very skilled in climbing. You tumble "+
	    "back to the floor."));
	SAY(" starts to climb the ladder, but tumbles back down.");
	return 1;
    }
    NFN0("Climb what?");
} /* climb */


/*
 * Function name:	look_pen
 * Description	:	describe pen, including any livings present
 * Returns	:	string description
 */
public string
look_pen()
{
    object *in_pen;

    FIX_EUID;
    PEN->short();

    if (!CAN_SEE_IN_OTHER_ROOM(TP, PEN))
    {
	return "It is too dark to see in the pen.\n";
    }

    in_pen = FILTER_CAN_SEE(FILTER_LIVE(all_inventory(find_object(PEN))),
	TP);

    switch (sizeof(in_pen))
    {
    case 0:
    	return "The pen is probably used to hold livestock.\n";
    case 1:
	return BSN(in_pen[0]->query_Art_name(TP)+
	    " is standing in the livestock pen.");
    default:
	return BSN(capitalize(COMPOSITE_LIVE(in_pen))+
	    " are standing in the livestock pen.");
    }
    /* NOTREACHED */
} /* look_pen */
