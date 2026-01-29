/*
 * /d/Gondor/river/anduin/lorien2rauros/pierwest.c
 *
 * Copyright (C) 1998 by Nancy L. Mintz (Gnadnar)
 *
 * west end of the low pier of stone at pool22
 */

#pragma strict_types

inherit "/d/Gondor/std/water/shore_room";
inherit "/d/Gondor/common/lib/tod_descs";

#include <stdproperties.h>	/* for OBJ_S_WIZINFO, etc */
#include "/d/Gondor/defs.h"	/* always */
#include "/d/Gondor/std/water/water_room.h"	/* for OBJ_I_WATER_MOVE */
#include "../anduin.h"

#define	POOL	(LORIEN_TO_RAUROS_DIR+"pool22")


/* prototypes */
public void	create_shore_room();
public void	msgs_before_move(object tp, string verb, string watertype);
public void	msgs_after_move(object tp, string vb, string pcpl);
public int	move_msg();


/*
 * Function name:	create_shore_room
 * Description	:	set up the pier
 */
public void
create_shore_room()
{
    add_prop(OBJ_S_WIZINFO,
	BSN("1 mile below sarn gebir, 339 miles downstream from "+
	    "the silverlode"));
    set_short("west end of a stone pier");

    /* use tod_descs to append time-of-day descriptions to long
     * and to handle sky items
     */
    set_tod_long(
	"To the east, the pier juts far out into the Anduin. "+
	"Towards land, it curves northwest to form a "+
	"low stony beach.");
    set_tod_prependshort(1);
    set_tod_landname("the Emyn Muil");
    set_tod_landtype("pier");
    set_long(tod_descs);
    add_item( ({ "sky", "sun", "moon", "star", "stars" }), tod_descs );

    set_water("north",
	({ "shallow pool", "waters", "water", "pool", }) );

    add_exit("pool22", "north", 0, 2, 1);
    add_exit("pool22", "northeast", 0, 2, 1);
    add_exit("piereast", "east", 0, 2);
    add_exit("beach22w", "northwest", move_msg, 2, 1);

    set_no_exit_msg( ({ "southeast", "south", "southwest", "west", }),
	BSN("You find no path through the scree."));


    add_item( ({ "waters", "water", "calm shallow pool", 
	"calm pool", "shallow pool", "pool", }),
	&exa_water(POOL,
	BSN("The pool seems to have been scooped in the river-side by "+
	"the water swirling down from Sarn Gebir against the stone pier. "+
	"It appears relatively sheltered, and not very deep.")));
    add_item( ({ "stone pier", "pier", }),
	BSN("The pier is formed of rough gray stone, perhaps three "+
	"feet wide. It protrudes east into the river."));
    add_item( ({ "rough gray stone", "rough stone", "gray stone",
	"stone" }),
	BSN("The rough gray stone is slightly damp."));
    add_item( ({ "great river", "river anduin", "anduin river",
	"anduin", "river" }),
	BSN("The Great River swirls against the stone pier as it "+
	    "races south between the cliffs of the Emyn Muil."));
    add_item( ({ "emyn muil" }),
	BSN("The cliffs of the Emyn Muil are bare and unwelcoming."));
    add_item( ({ "land", "river-side", "shore", "shores", "river bank",
	"river banks", "bank", "banks", "western shore",
	"western bank", "west shore", "west bank", }),
	BSN("Steep cliffs line both shores. To the west, there "+
	    "appears to be a trail leading inland below the cliffs."));
    add_item( ({ "western cliff", "western cliffs", "west cliff",
	"west cliffs", "limestone cliff", "limestone cliffs", 
	"cliff", "cliffs", }),
	BSN("Limestone cliffs rise above jumbled scree inland."));
    add_item( ({ "eastern shore", "eastern bank", "east shore",
	"east bank", "eastern cliff", "eastern cliffs", "east cliff",
	"east cliffs" }),
	BSN("Steep cliffs rise along the east shore, although it is "+
	    "difficult to see details from here."));
    add_item( ({ "inland", "narrow trail", "trail", }),
	BSN("A narrow trail leads west from the stony beach into "+
	    "the scree below the cliffs."));
    add_item( ({ "low stony beach", "low beach", "stony beach", "beach" }),
	BSN("A low beach of gray stone runs along the western "+
	    "edge of the pool."));
    add_item( ({ "tumbled boulder", "tumbled boulders",
	"tumbled rock", "tumbled rocks", "boulder", "boulders",
	"rock", "rocks", "jumbled scree", "scree", }),
	BSN("Rocks and boulders of all sizes are tumbled below "+
	    "the cliffs to the east and south."));

} /* create_shore_room */


/*
 * Function name:	msgs_before_move
 * Description	:	roll our own you-enter-the-water msgs
 * Arguments	:	object tp -- this_player
 *			string verb -- swim, wade, dive, ...
 *			string watertype -- river, pool, ....
 */
public void
msgs_before_move(object tp, string verb, string watertype)
{
    WRITE("You jump off the pier into the shallow pool.");
    SAY(" jumps off the pier into the shallow pool.");
    tp->add_prop(OBJ_I_WATER_MOVE, WATER_MOVE_WADE);
} /* msgs_before_move */


/*
 * Function name:	msgs_after_move
 * Description	:	provide a convenient place for inheriting
 *			rooms to roll their own foo-arrives msgs
 * Arguments	:	object tp -- this_player
 *			string vb -- "swim", "wade", "dive"
 *			string pcpl -- participle phrase suitable for being
 *				appended to "Foo arrives " (e.g., "swimming")
 *				(no trailing period)
 *
 * we have to explicitly set and restore this_player here or
 * when teams move, you will see some team member enter twice
 * and will not see the team leader enter at all.
 */
public void
msgs_after_move(object tp, string vb, string pcpl)
{
    object	save_tp;

    save_tp = TP;
    set_this_player(tp);
    SAY(" jumps from the stone pier and lands in the pool with a splash.");
    set_this_player(save_tp);
} /* msgs_after_move */


/*
 * Function name:	move_msg
 * Description	:	msg for the nw exit
 * Returns	:	0 -- exit always allowed
 */
public int
move_msg()
{
    WRITE("You leap from the pier onto the beach.");
    return 0;
} /* move_msg */
