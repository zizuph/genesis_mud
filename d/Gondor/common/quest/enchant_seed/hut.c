/*
 *	/d/Gondor/common/quest/enchant_seed/hut.c
 *
 *	A hut in Druedain Forest where a retired ranger lives.
 *
 *	Coded by Elessar 1992
 *
 *	Modification log:
 *	15-Feb-1997, Olorin:	General revision.
 *      14-Mar-2013, Gorboth:   Removed death trap, allowing escape
 */	

#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include <filter_funs.h>
#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"


public void	create_gondor();
public void	reset_room();
public void	init();
public int	block_search(string arg);
public int	make_bed(string arg);
public int	test_blocked();

static object	Ranger;
static int	Bed_is_made;


/*
 * Function name:	create_gondor
 * Description	:	set up the hut
 */
public void
create_gondor()
{
    set_short("inside a small hut");
    set_long(BSN("The hut is small, its furnishings simple, and "+
	"its fireplace empty and neatly swept. An open door "+
	"and a narrow window above the bed admit some light, and "+
	"a faint odour of herbs gives a certain freshness to the air."));
	/* "admit some light"? what if it's night? */

    add_prop(ROOM_I_INSIDE, 1);

    add_item("furnishings",
	BSN("There is not much here except a bed, chair and table, " +
	"and a fireplace with a few battered pots stacked on the " +
	"mantelpiece."));
    add_item("bed",
	BSN("The low, narrow bed is slightly rumpled, as if it had "+
	"been slept in quite recently."));
    add_item("chair",
	BSN("The rickety wooden chair appears to have been made "+
	"by an inexperienced carpenter."));
    add_item("table",
	BSN("The table wobbles on uneven legs, and its surface "+
	"is rough and unfinished."));
    add_item( ({ "uneven legs", "table legs", "legs" }),
	"The table legs are of somewhat different lengths.\n");
    add_item( ({ "surface", "table surface" }),
	"The surface of the table is quite clean, but far from polished.\n");
    add_item("fireplace","There is no fire in the fireplace right now.\n"+
	BSN("There is neither fire nor ashes in the fireplace, and its "+
        "mantelpiece holds only a few pots."));
    add_item( ({ "battered pot", "pot", "battered pots", "pots" }),
	"The pots are scratched and worn, but quite clean.\n");
    add_item( ({ "thick plank", "plank", "mantelpiece", "mantel" }),
	BSN( "The mantel is just a thick plank across the top of the "+
	"fireplace. It holds few battered pots."));
    add_item( ({ "narrow window", "window" }),
	BSN("The window is just a pane of yellowed glass set into the wall. "+
	"It cannot be opened."));
    add_item( ({ "pane", "yellowed glass", "glass" }),
	"The glass of the window is yellowed with age.\n");
    add_item( ({ "hut door", "open door", "door" }),
	BSN("The door is of plain unstained wood. It is open."));
    add_item( ({ "floor", "wall", "walls" }),
	"Walls and floor are weathered wood, clean and unadorned.\n");
    add_item( ({ "weathered wood", "wood" }),
	"The wood has weathered to a soft grey colour.\n");
    add_item("ceiling",
	BSN("The hut has no proper ceiling. All that's overhead is "+
	"the underside of the roof."));
    add_item( ({ "wide timbers", "timbers", "underside", "roof" }),
	"The wide timbers of the roof fit tightly together.\n");

    add_cmd_item( ({ "narrow window", "window", "pane", "yellowed glass",
	"glass" }),
	({ "open", "close" }),
	"The window is permanently closed.\n");

    add_cmd_item( ({ "hut door", "open door", "door" }),
	"open",
	"The door already is open.\n");
    add_cmd_item( ({ "hut door", "open door", "door" }),
	"close",
	"The door resists your efforts to close it.\n");
    add_cmd_item(  ({ "hut door", "open door", "door",
    	"on hut door", "on open door", "on door" }),
	"knock",
	"You foolishly knock on the open door.\n");

    add_cmd_item( ({ "in chair", "on chair", "down in chair",
	"down on chair", "chair" }),
	"sit",
	"The chair is very rickety -- you decide to remain standing.\n");


    add_exit((COMMON_DIR + "quest/enchant_seed/garden"), "out", "@@test_blocked");

    reset_room();
} /* create_gondor */


/*
 * Function name:	reset_room
 * Description	:	be sure the ranger is here, mess up the
 *			bed if there aren't any players around.
 */
public void
reset_room()
{
    Ranger = clone_npc(Ranger, (COMMON_DIR + "quest/enchant_seed/rranger"));
    if (!sizeof(FILTER_PLAYERS(all_inventory(TO))))
    {
	remove_item("bed");
	add_item("bed",
	    BSN("The low, narrow bed is slightly rumpled, as if it had "+
	    "been slept in quite recently."));
    }
} /* reset_room */



/*
 * Function name:	init
 * Description	:	add verbs
 */
public void
init()
{
    ::init();
    add_action(block_search, "search");
    add_action(block_search, "rummage");
    add_action(make_bed,     "make");
    add_action(make_bed,     "tidy");
    add_action(make_bed,     "straighten");
} /* init */


/*
 * Function name:	block_search
 * Description	:	don't let 'em rummage hut if ranger is here
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	1 if we block, 0 if not
 */
public int
block_search(string arg)
{
    if (objectp(Ranger) &&
	ENV(Ranger) == TO)
    {
	write("You start to search.\n");
	SAY(" starts to search.");
	Ranger->command("say Please don't rummage around my hut!");
	Ranger->command("say That is very rude.");
	Ranger->command("glare "+TP->query_real_name());
	write("You stop searching.\n");
	return 1;
    }
    return 0;
} /* block_search */


/*
 * Function name:	make_bed
 * Description	:	respond to attempts to make the bed
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	1 on success, 0 on failure
 */
public int
make_bed(string arg)
{
    if (!strlen(arg) ||
	!parse_command(LOW(arg), ({}), "[up] [the] 'bed'"))
    {
	NF0(CAP(QVB)+" what?\n");
    }
    if (Bed_is_made)
    {
	NF0("The bed is already neatly made up.\n");
    }
    write("You "+QVB+" up the bed.\n");
    SAY(" tidies up the bed.");
    Bed_is_made = 1;
    remove_item("bed");
    add_item("bed", "The low, narrow bed is neatly made up.\n");
    return 1;
} /* make_bed */



/*
 * Function name:	test_blocked
 * Description	:	block exit if player is fighting the ranger
 */
public int
test_blocked()
{
    if (TP->query_attack()->id("ranger"))
    {
        TP->catch_msg(QCTNAME(TP->query_attack()) + " blocks your way out!\n");

        if (!random(5))
        {
            TP->catch_msg("Somehow you manage to move past him anyway!\n");
            return 0;
        }
    }
    return 0;
} /* test_blocked */
