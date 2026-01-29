/*
 * /d/Gondor/river/anduin/lorien2rauros/fishcamp_s.c
 *
 * Copyright (C) 1998 by Nancy L. Mintz (Gnadnar)
 *
 * south end of Beorning fish camp, just below carrock ford,
 * 35 miles north of old forest rd
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/water/shore_room";
inherit "/d/Gondor/common/lib/tod_descs";
inherit "/d/Gondor/common/lib/drink_water";
inherit "/d/Gondor/common/lib/dig";

#include "/d/Gondor/defs.h"	/* always */
#include "fishcamp.h"

#define	RIVER	(CARROCK_TO_LORIEN_DIR + "river01")

static object	Fisher;


/* prototypes */
public void	create_shore_room();
public void	reset_room();
public int	move_msg();
public void	dig_results(object digger);
public int	unq_move(string arg);


/*
 * Function name:	create_shore_room
 * Description	:	set up the beach
 */
public void
create_shore_room()
{
    set_short("beach");

    /* use tod_descs to append time-of-day descriptions to long
     * and to handle sky items
     */
    set_tod_long(
        "A wide sandy beach runs between the Anduin to the west and a " +
        "large wall-less shelter to the east. Just above the beach, " +
	"the river splits to flow around a great rock.");
    set_tod_landname("the vale of Anduin");
    set_tod_landtype("riverbank");
    set_long(tod_descs);
    add_item( ({ "sky", "sun", "moon", "star", "stars" }), tod_descs );

    set_water("west",
	({ "great river", "waters", "water", "river", "anduin",
	"river anduin", "anduin river" }) );

    /* moving in deep sand is tiring */
    add_exit("fishcamp_n", "northeast", move_msg, 5);
    add_exit("river01", "west", 0, 5, 1);
    add_exit("beach02e", "south", move_msg, 5);
    add_exit((CARROCK_TO_LORIEN_DIR + "boatshelter"), "east", 0, 5, 1);
    add_exit((CARROCK_TO_LORIEN_DIR + "boatshelter"), "enter", 0, 5, 1);

    set_no_exit_msg( ({ "north", "northwest", "southwest" }),
	BSN("You wander along the beach for a while."));
    set_no_exit_msg( ({ "southeast", }),
	BSN("You strike a course inland, but soon lose your way " +
	    "and return to the river."));

    add_item( ({ "great river", "river anduin", "anduin river",
	"anduin", "river", "waters", "water", }),
	&exa_water(RIVER,
	    BSN("Just upstream of the beach, a great rock rises " +
		"in the middle of the Anduin, which has split to " +
		"flow around the mass of stone. Below the rock, " +
		"the waters move swiftly south.")));

    add_item( ({ "western bank", "west bank", "far shore", "far side",
	"far side of river", "western shore", "west shore" }),
	BSN("Nothing is visible on the far shore but grass."));
    add_item( ({ "this shore", "this side", "this side of river",
	"bank", "riverbank", "river bank", "edge",
	"shore", "shores", "eastern bank", "east bank", "eastern shore",
	"east shore" }),
	BSN("Beyond the sandy beach, this side of the river is covered with " +
	    "grass, which grows even taller and more lush inland."));
    add_item( ({ "inland", "tall grass", "tall grasses",
	"lush grasses", "lush grass", "grasses", "grass", }),
	BSN("Tall grasses, tossing in the least breath of wind, " +
	    "block all views inland."));
    add_item( ({ "wide sandy beach", "wide beach", "sandy beach",
	"beach", }),
	"The beach is fairly wide, and its sand appears deep.\n");
    add_item( ({ "ground", "coarse grey sand", "coarse sand",
        "grey sand", "sand", }),
        BSN("The coarse grey sand underfoot seems quite deep."));
    add_item( ({ "water", "anduin river", "great river", "river anduin",
        "river", }),
        BSN("The Great River flows south, wide and quite swift."));
    add_item( ({ "large wall-less shelter", "large shelter",
        "wall-less shelter", "shelter", }),
        BSN("The shelter has a flat lathe-and-canvas roof, supported " +
            "by sturdy timbers. It would not provide much protection " +
            "from severe weather."));
    add_item( ({ "lathe-and-canvas roof", "roof", }),
        BSN("The shelter roof is just a piece of canvas stretched over " +
            "a lathe framework."));
    add_item( ({ "lathe framework", "framework", "lathe", }),
        "Not much of the framework is visible from here.\n");
    add_item( ({ "piece of canvas", "canvas", }),
        BSN("Canvas is stretched over the lathe framework and tied to " +
        "the supporting timbers. What can be seen of the canvas " +
        "appears old and worn."));
    add_item( ({ "supporting timber", "supporting timbers",
	"sturdy timber", "timber", "sturdy timbers", "timbers", }),
        BSN("The timbers supporting the shelter roof are fairly large. " +
            "They appear much more sturdy than the roof itself."));
    add_item( ({ "west shore", "far shore" }),
        BSN("The far shore is not clearly visible from this distance."));
    add_item( ({ "rock", "lump", "lump of rock", "massive lump of rock",
	"mass of rock", "stone", "lump", "lump of stone",
	"massive lump of stone", "mass of stone", "island", "carrock", }),
        BSN("The Carrock is a massive lump of rock, rising from the " +
	    "middle of the Anduin just upstream of the beach."));

    reset_room();


    set_drink_from( ({ "great river", "river anduin", "anduin river",
	"anduin", "river", }) );

    set_dig_pattern("[in] [the] [coarse] [brown] [grey] " +
	"[and] [brown] 'sand' / 'here'");
    set_dig_message("in the sand");

} /* create_shore_room */


/*
 * Function name:	reset_room
 * Description	:	clone up the fisher who teach boating,
 *			and sells boats on the side.
 */
public void
reset_room()
{
    Fisher = clone_npc(Fisher, FISHER_FILE);
}

/*
 * Function name:	init
 * Description	:	add drink verb and "dig"
 */
public void
init()
{
    ::init();
    init_drink();
    add_action(dig_here,	"dig");
}


/*
 * Function name:	move_msg
 * Description	:	do some you-move atmospheric msgs
 * Returns	:	int -- 0 (exit always allowed)
 */
public int
move_msg()
{
    switch(QVB)
    {
    case "northeast":
	WRITE("You follow the riverbank to the northeast, where " +
	    "the grasses give way to a sandy beach.");
	break;
    case "south":
	WRITE("You leave the beach and head south through " +
	    "thick, tangled grass.");
	break;
    }
    return 0;
} /* move_msg */


/*
 * Function name:	dig_results
 * Description	:	give results of digging
 * Arguments	:	object digger -- the person digging
 */
public void
dig_results(object digger)
{
    tell_object(digger, "You find nothing buried in the sand.\n");
} /* dig_results */


/*
 * Function name:	unq_move
 * Description	:	mask parent to handle "enter shelter"
 * Arguments	:	string arg - the command line argument.
 * Returns	:	1 on success, 0 on failure
 */
public int
unq_move(string arg)
{
    if (QVB != "enter" ||
	(strlen(arg) &&
	 parse_command(LOW(arg), ({}),
	    "[the] [large] [wall-less] 'shelter'")))
    {
	return ::unq_move(arg);
    }
    return 0;
} /* unq_move */
