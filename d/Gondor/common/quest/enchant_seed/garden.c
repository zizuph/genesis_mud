/*
 *	/d/Gondor/common/quest/enchant_seed/garden.c
 *
 *	Coded 1992 by Elessar.
 *
 *	Modification log:
 *	29-Jan-1997, Olorin:	General revision.
 *      02-Sep-1998, Gnadnar:	tidy up
 */

#pragma strict_types

inherit "/d/Gondor/std/room.c";
inherit "/d/Gondor/common/lib/herbsearch.c";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

public void	create_gondor();
public void	init();
public int	enter_hut(string arg);
public int	do_get(string arg);

/*
 * Function name:	create_gondor
 * Description	:	set up the hut
 */
public void
create_gondor()
{
    set_short("a small garden outside a hut");
    set_long(BSN("A green and and well kept garden surrounds a little "
	+ "wooden hut. On the wall of the hut, next to the open door, "
	+ "a couple of new-caught rabbits have been salted and hung up "
	+ "to dry. Beyond the hut and garden, the dark Druedain Forest looms. "
	+ "A path leads west into the forest."));

    set_up_herbs( ({ (HERB_DIR + "lothore"), (HERB_DIR + "redweed") }),
		  ({ "garden", }), 2);
    add_item( ({ "ground", "soil", "dirt" }),
	BSN("The dark soil appears rich and fertile."));
    add_item( ({ "small garden", "garden", }),
	BSN("The garden is not really big, only about ten meters square, "+
	"but it is filled with flowers, vegetables and other plants. "+
	"Beyond the garden looms the Druedain Forest."));
    add_item(({ "flower", "flowers", }),
	BSN("Flowers of several colors grow here, and the "+
        "scent of them is refreshening."));
    add_item( ({ "plant", "plants", }),
	BSN("Many plants grow thickly in the garden -- flowers, vegetables "+
        "and even some that look like herbs."));
    add_item( ({ "herb", "herbs", }),
	BSN("It is hard to determine, at a glance, which of the plants are "+
        "herbs and which are not. A careful search might help."));
    add_item( ({ "vegetable", "vegetables", }),
	BSN("The vegetables appear to thrive in the small garden."));
    add_item( ({ "rabbits", "rabbit", }),
	BSN("The rabbits look freshly killed. Probably they're "+
	"destined for someone's dinner pot."));
    add_item( ({ "little wooden hut", "wooden hut", "little hut", "hut" }),
    	BSN("The hut is made of weathered wood. It is not very big, but "+
	"appears solid. Its door stands ajar."));
    add_item( ({ "weathered wood", "wood" }),
	"The wood has weathered to a soft grey colour.\n");
    add_item( ({ "hut door", "open door", "door" }),
	BSN("The door is of plain unstained wood. It is open."));

    add_cmd_item( ({ "flower", "flowers", "garden", "small garden",
	"plant", "plants", "vegetable", "vegetables", "herb", "herbs" }),
	"smell",
	BSN("The aroma of the garden is most enticing. Flowers, vegetables "+
	"and herbs combine to produce a heady green fragrance."));

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

    set_noshow_obvious(1);

    add_exit(DRUEDAIN_DIR + "forest12",             "north",         0, 1);
    add_exit(DRUEDAIN_DIR + "forest13",             "east",          0, 1);
    add_exit(DRUEDAIN_DIR + "forest11",             "south",         0, 1);
    add_exit(DRUEDAIN_DIR + "forest9",              "west",          0, 1);

} /* create_gondor */


/*
 * Function name:	init
 * Description	:	add verbs
 */
public void
init()
{
    ::init();
    add_action(enter_hut, "enter");
    add_action(do_get,    "get");
    add_action(do_get,    "take");
    add_action(do_get,    "pick");
} /* init */


/*
 * Function name:	enter_hut
 * Description	:	handle attempts to enter
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	1 on success, 0 on failure
 */
public int
enter_hut(string arg)
{
    if (arg == "hut" ||
        arg == "door" ||
        arg == "little wooden hut" ||
        arg == "wooden hut" ||
        arg == "little hut" ||
        arg == "hut door" ||
        arg == "open door")
    {
	write("You enter the wooden hut.\n");
	TP->move_living("into the hut", (COMMON_DIR + "quest/enchant_seed/hut"));
	return 1;
    }
    NF0("Enter what?\n");
} /* enter_hut */


/*
 * Function name:	do_get
 * Description	:	handle attempts to get room items
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	1 on success, 0 on failure
 *
 * must do this here, not via add_cmd_item(), or players will not
 * be able to pick up real flowers, herbs etc lying in the room.
 */
public int
do_get(string arg)
{
    if (!strlen(arg) ||
        member_array(arg, 
	    ({ "vegetable", "vegetables", "herb", "herbs", "flower",
	       "flowers", "rabbit", "rabbits", "plant", "plants", })) < 0 ||
	objectp(present(arg, TO)))
    {
	return 0;
    }
    WRITE("You reach out, but suddenly feel very ashamed of your "+
	    "larcenous impulse. You decide not to take anything.");
    return 1;
} /* do_get */
