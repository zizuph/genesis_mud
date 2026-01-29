/*
 * /d/Gondor/river/anduin/lorien2rauros/piereast.c
 *
 * Copyright (C) 1998 by Nancy L. Mintz (Gnadnar)
 *
 * east end of the low pier of stone at pool22
 */

#pragma strict_types

inherit "/d/Gondor/std/water/shore_room";
inherit "/d/Gondor/common/lib/tod_descs";

#include <stdproperties.h>	/* for OBJ_S_WIZINFO, etc */
#include "/d/Gondor/defs.h"	/* always */
#include "/d/Gondor/std/water/water_room.h"	/* for OBJ_I_WATER_MOVE */
#include "../anduin.h"

#define	POOL	(LORIEN_TO_RAUROS_DIR+"pool22")
#define	RIVER	(LORIEN_TO_RAUROS_DIR+"river22")


/* prototypes */
public void	create_shore_room();
public void	msgs_before_move(object tp, string verb, string watertype);
public void	msgs_after_move(object tp, string vb, string pcpl);

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
    set_short("east end of a stone pier");

    /* use tod_descs to append time-of-day descriptions to long
     * and to handle sky items
     */
    set_tod_long(
	"The waters of the Anduin swirl past, splashing against "+
	"the stone. To the west, the pier encloses a shallow pool.");
    set_tod_prependshort(1);
    set_tod_landname("the Emyn Muil");
    set_tod_landtype("pier");
    set_long(tod_descs);
    add_item( ({ "sky", "sun", "moon", "star", "stars" }), tod_descs );

    set_water("northwest",
	({ "calm shallow pool", "calm pool", "shallow pool", "pool", }) );
    set_water("north",
	({ "great river", "waters", "water", "river", "anduin",
	    "river anduin", "anduin river" }) );
    set_water("northeast",
	({ "great river", "waters", "water", "river", "anduin",
	    "river anduin", "anduin river" }) );
    set_water("east",
	({ "great river", "waters", "water", "river", "anduin",
	    "river anduin", "anduin river" }) );
    set_water("southeast",
	({ "great river", "waters", "water", "river", "anduin",
	    "river anduin", "anduin river" }) );
    set_water("south",
	({ "great river", "waters", "water", "river", "anduin",
	    "river anduin", "anduin river" }) );
    set_water("southwest",
	({ "great river", "waters", "water", "river", "anduin",
	    "river anduin", "anduin river" }) );

    add_exit("pierwest", "west", 0, 2);
    add_exit("pool22", "northwest", 0, 2, 1);
    add_exit("river22", "north", 0, 2, 1);
    add_exit("river22", "northeast", 0, 2, 1);
    add_exit("river22", "east", 0, 2, 1);
    add_exit("river22", "southeast", 0, 2, 1);
    add_exit("river22", "south", 0, 2, 1);
    add_exit("river22", "southwest", 0, 2, 1);

    add_item( ({ "great river", "waters", "water", "river", "anduin",
	"river anduin", "anduin river" }),
	&exa_water(RIVER, 
	    "The Anduin swirls and foams past the pier of stone.\n"));
    add_item( ({ "calm shallow pool", "calm pool", "shallow pool",
	"pool", }),
	&exa_water(POOL,
	BSN("The pool seems to have been scooped in the river-side by "+
	"the water swirling down from Sarn Gebir against the stone pier. "+
	"It appears relatively sheltered, and not very deep.")));
    add_item( ({ "easternmost tip", "tip", "stone pier", "pier", }),
	BSN("The pier is formed of rough gray stone, perhaps three "+
	"feet wide. From this easternmost tip, it stretches west "+
	"past a shallow pool towards shore."));
    add_item( ({ "rough gray stone", "rough stone", "gray stone",
	"stone" }),
	BSN("The rough gray stone is wet and splippery."));
    add_item( ({ "land", "emyn muil" }),
	BSN("The cliffs of the Emyn Muil enclose the river, rising "+
	    "sheer and unwelcoming on either shore."));
    add_item( ({ "wall", "walls", "wall of gray stone", 
	"walls of gray stone", "cliff", "cliffs", }),
	BSN("Gray stone rises almost vertically on both sides "+
	    "of the river."));
    add_item( ({ "gnarled fir", "gnarled firs", "fir", "firs",
	"tree", "trees" }),
	BSN("High above the water, a few gnarled firs cling "+
	    "to the cliffs."));
    add_item( ({ "river-side", "shore", "shores", "river bank",
	"river banks", "bank", "banks", "western shore",
	"western bank", "west shore", "west bank", }),
	BSN("Beyond a low beach, the shore rises sheer into a gray "+
	    "cliff. There seems to be some kind of a cleft in the stone."));
    add_item( ({ "western cliff", "western cliffs", "west cliff",
	"west cliffs" }),
	BSN("Steep cliffs line both shores. To the west, there "+
	    "appears to be a trail leading inland."));
    add_item( ({ "eastern shore", "eastern bank", "east shore",
	"east bank", "eastern cliff", "eastern cliffs", "east cliff",
	"east cliffs" }),
	BSN("The cliffs along the eastern shore loom over the river, "+
	    "harsh and unwelcoming."));
    add_item( ({ "inland", "narrow trail", "trail", }),
	BSN("There's some kind of a trail on the western shore, "+
	    "but it is difficult to see details from here."));
    add_item( ({ "low stony beach", "low beach", "stony beach", "beach" }),
	BSN("Beyond the pool, the pier curves north to form "+
	    "a low beach of gray stone."));

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
    WRITE("You jump off the pier into the Anduin.");
    SAY(" jumps off the pier into the Anduin.");
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
    SAY(" jumps from the stone pier and lands in the river with a splash.");
    set_this_player(save_tp);
} /* msgs_after_move */
