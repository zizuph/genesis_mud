#pragma strict_types
/*
 * ~/steps_n.c
 *
 * Northern Entrance to the Public Bath
 *
 * Revisions:
 *   Grace,  Feb 1994: Created.
 *   Grace,  Aug 1994: ?
 *   Lucius, Oct 2008: Cleanup.
 *   Lucius, Aug 2016: Recoded baths.
 *
 */
#include "../bath.h" 
inherit BATH_ROOM;


static void
create_bath_room(void)
{
    set_short("North steps of the public bath");
    set_long("Water laps your toes as you stand at the top of a series "+
	"of steps leading down into the warm pool. People of many "+
	"races visit this bath to wash off the dirt of travel and "+
	"the sweat of battle. The nebulous shapes of patrons and "+
	"bath attendants can be seen through the obscuring mists. "+
	"The scent of herbs is strong, but not overwhelming."+
	"@@bath_view@@\n");

    add_item("water",
	"It is surprisingly clear and quite warm.\n");
    add_item("steps",
	"They are made of marble and lead down into the water.\n");
    add_item("pool",
	"From this vantage you can see that is it many man-lengths "+
	"in diameter. It looks very inviting, so why not enter it?\n");
    add_item(({"patrons", "attendants", "people"}),
	"The steam rising from the pool makes it difficult to "+
	"determine more than that the dark outlines you see are of "+
	"bipedal shapes.\n");

    MIST;

    add_exit(BATHRM + "arc_n", "north");
    add_exit(BATHRM + "pub_bath", "south", enter_desc, 1, 1);
}

public void 
init(void)
{
    ::init();

    add_action(enter_pool, "enter");
    add_action(enter_pool, "step");
    add_action(enter_pool, "wade");
}
