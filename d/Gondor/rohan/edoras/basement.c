/*
 * /d/Gondor/rohan/edoras/basement.c
 *
 * Modification history:
 *	16-April-1998, Gnadnar:	add culvert, conform to domain.rules.
 */

#pragma strict_types

inherit "/d/Gondor/std/room";
inherit "/d/Gondor/common/lib/drink_water";

#include <stdproperties.h>
#include "/d/Gondor/defs.h"

/* prototypes */
public void	create_gondor();
public void	reset_room();
public void	init();
public int	do_dig(string arg);
public string	look_floor();

static int     Bag_found = 0;

/*
 * Function name:	create_gondor
 * Description	:	set up the room
 */
public void
create_gondor()
{
    set_short("Stable basement");
    set_long(BSN("The dingy basement smells of damp stone "
      + "and old earth. Water flows in a culvert along "
      + "the base of the east wall."));
    add_prop(ROOM_I_INSIDE, 1);

    add_exit("rooms/edtransport", "up", 0);
    add_exit("basement2", "north", 0);

    add_item( ({ "walls", "wall" }),
	"The walls are damp, dirty stone.\n");
    add_item( ({ "floor", "ground", "dirt", "earth" }), look_floor);
    add_item( ({ "stone culvert", "culvert", "stone-lined channel",
	"channel", }),
	BSN("The culvert is just a narrow, stone-lined channel "+
	    "running along the base of the east wall."));
    add_item( ({ "water" }),
	BSN("The water flows north in the culvert.  It appears "+
	    "to be quite clean."));
    add_item( ({ "stones", "stone" }),
	"The walls and culvert are built of dark gray stone.\n");

    add_cmd_item( ({ "air", "basement", "stone", "stones", }),
	({ "sniff", "smell" }),
	BSN("The basement has a dank, damp smell."));

    set_drink_from( ({ "stone culvert", "culvert",
	"stone-lined channel", "channel" }) );
} /* create_gondor */


/*
 * Function name:	reset_room
 * Description	:	clear Bag_found flag
 */
public void
reset_room()
{
    ::reset_room();
    Bag_found = 0;
} /* reset_room */


/*
 * Function name:	init
 * Description	:	add drink and dig verbs
 */
public void
init()
{
    ::init();
    init_drink();
    add_action("do_dig", "dig");
} /* init */


/*
 * Function name:	do_dig
 * Description	:	handle attempts to dig here
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	1 on success, 0 on failure
 */
public int
do_dig(string arg)
{
    object	bag,
		tp;

    if (!strlen(arg) ||
	!parse_command(arg, ({}),
	    "[in] 'ground' / 'here' [with] [shovel]"))
    {
        return 0;
    }

    tp = TP;
    if (!objectp(present("shovel", tp)))
    {
        write("You find that digging in the firm ground without a "+
	      "shovel is impossible.\n");
        SAY(" tries to dig in the ground with "+
		POSSESSIVE(tp)+" hands, but fails.");
        return 1;
    }
    write("You dig into the ground with the shovel.\n");
    SAY(" digs in the ground with a shovel.");

    if (!Bag_found)
    {
        write("You uncover a bag!\n");
        Bag_found = 1;
        bag = clone_object(ROH_DIR + "edoras/obj/bag");
        clone_object(ROH_DIR + "edoras/obj/diamond")->move(bag, 1);
        clone_object(ROH_DIR + "edoras/obj/fknife")->move(bag, 1);
	bag->move(TO);
    }
    return 1;
} /* do_dig */


/*
 * Function name:	look_floor
 * Description	:	VBFC for the floor state
 * Returns	:	string -- floor description
 */
public string
look_floor()
{
    if (!Bag_found)
    {
	return "Bare, packed earth is underfoot.\n";
    }
    return "The earth underfoot seems to have been recently disturbed.\n";
} /* look_floor */
