/*
 * /d/Gondor/lebennin/sirith/farms/farm1/smokehouse.c
 * smokehouse of large farmstead in southern lebennin
 *
 * Copyright (C) 1997 by Nancy L. Mintz (Gnadnar)
 * Finwe,May 2019: Removed hidden exits
 *
 */

#pragma strict_types

#include <stdproperties.h>		/* for ROOM_I_LIGHT	*/
#include "/d/Gondor/defs.h"
#include "../defs.h"			
#include "/d/Gondor/open/fireplace/fireplace.h"

inherit "/d/Gondor/lebennin/sirith/room";
inherit "/d/Gondor/open/fireplace/fireplace";

public void	create_sirith();
public void	reset_room();
public void	init();
public string	fire_desc(string arg);		/* VBFC for fire */


/*
 * Function name:	create_sirith
 * Description	:	set up the room
 */
public void
create_sirith()
{
    set_short("a large shed");
    set_long(fire_desc);

    /* since a smokehouse should be very tightly sealed, the room
     * is dark unless the fire is burning or the door is open.
     */
    add_prop(ROOM_I_LIGHT, 0);
    add_prop(ROOM_I_INSIDE, 1);

    add_exit("northyard", "south", 0, 2);
    set_door(SIRITH_FARMS_DIR + "obj/f1_smokeh_door2");
    set_no_exit_msg( ({ "north", "northeast", "east", "southeast",
	"southwest", "west", "northwest", "up", "down" }),
	BSN("You wander around the shed.") );

    set_dark_room_ok(1);

    set_fire_container("fire pit");
    /* this will match "the fire firepit", but it's probably worth
     * it in order to match either "the pit" or "the fire pit" or 
     * "the firepit"
     */
    set_parse_pattern("[the] [fire] 'pit' / 'firepit'");
    add_item( ({ "ground", "floor", "firepit", "fire pit", "pit" }),
	&fire_desc("fire pit"));
    add_item( ({ "fire" }),
	&fire_desc("fire"));
    add_item( ({ "wood", "firewood", "wood in firepit",
		 "firewood in firepit", "wood in fire pit",
		 "firewood in fire pit" }),
	&fire_desc("wood"));
    add_item( ({ "ash", "ashes" }),
	&fire_desc("ash"));
    add_item( ({ "smoke", "air" }),
	&fire_desc("smoke"));

    add_item( ({ "bundle", "bundles", "meat", "meats",
		 "cuts of meat", "cut of meat" }),
	BSN("The bundles appear to be cuts of meat, "+
	    "of all shapes and sizes, "+
	    "wrapped with twine and hung from the rafters."));
    add_item( ({ "twine" }),
	BSN("Twine wraps around the meats and loops "+
	    "over the rafters."));
    add_item( ({ "rafter", "rafters", "ceiling", "gloom" }),
	BSN("Various bundles dangle from the rafters."));
    add_item( ({ "wall", "walls", "log", "logs", "caulk", "caulking" }),
	BSN("The log walls are well caulked."));
    add_item( ({ "stone", "stones" }),
	BSN("Large, round stones line the fire pit."));

    add_cmd_item( ({ "bundle", "bundles", "meat", "meats", "cuts of meat",
		 "cut of meat" }),
	({ "get", "take", "search" }),
	BSN("The meats dangle overhead, well out of reach."));
    add_cmd_item( ({ "smoke", "air" }), ({ "smell", "sniff", "inhale" }),
	BSN("The smoke has a slightly sweet, fruity aroma."));
 
    reset_room();
} /* create_sirith */


/*
 * Function name:	reset_room
 * Description	:	replenish wood and fire
 */
public void
reset_room()
{
    set_wood(-1);
    /* XXX this is not very plausible .. who lights it ? */
    if (query_fire_state() != FIRE_BURNING)
    {
	set_fire_state(FIRE_BURNING);
    }
} /* reset_room */


/*
 * Function name:	init
 * Description	:	add fire verbs
 */
public void
init()
{
    ::init();
    init_fire();
} /* init */


/*
 * Function name:	fire_desc
 * Descripiton	:	VBFC for fireplace
 * Arguments	:	string arg -- what we're looking at
 * Returns	:	string description
 *
 * except for the room long (default case), the caller is expected to
 * do BSN(), so no newlines in returned description
 */
public string
fire_desc(string arg)
{
    int	fire_state = query_fire_state();

    switch (arg)
    {

    case "fire pit":
	switch (fire_state)
	{
	case FIRE_BURNING:
	    return BSN(
		"The fire pit is a deep, stone-lined depression in "+
		"the center of the floor. A fire burns steadily "+
		"in the pit, filling the shed with aromatic smoke.");
	case FIRE_UNLIT_WOOD:
	    return BSN(
		"The fire pit is a deep, stone-lined depression in "+
		"the center of the floor. Firewood is piled in the pit.");
	default:	/* FIRE_ASHES */
	    return BSN(
		"The fire pit is a deep, stone-lined depression in "+
		"the center of the floor, holding nothing but ashes.");
	}

    case "fire":
	if (fire_state == FIRE_BURNING)
	{
	    return BSN(
		"A fire burns steadily in the fire pit, "+
		"filling the shed with aromatic smoke.");
	}
	return "You find no fire.\n";

    case "wood":
	switch (fire_state)
	{
	case FIRE_BURNING:
	    return BSN(
		"The wood in the fire pit burns quietly and steadily, "+
		"and gives off an aromatic smoke.");
	case FIRE_UNLIT_WOOD:
	   return BSN(
		"Unlit wood is piled in the fire pit.");
	default:	/* FIRE_ASHES */
	    return "You find no "+Exa_arg+".\n";
	}

    case "ash":
	switch (fire_state)
	{
	case FIRE_BURNING:
	    return BSN(
		"Beneath the smoky fire, "+
		"ashes cover the bottom of the fire pit.");
	case FIRE_UNLIT_WOOD:
	    return BSN(
		"Beneath the unlit wood, "+
		"ashes cover the bottom of the fire pit.");
	default:	/* FIRE_ASHES */
	    return BSN(
		"Ashes cover the bottom of the fire pit.");
	}

    case "smoke":
	if (fire_state == FIRE_BURNING)
	{
	    return BSN(
		"An aromatic smoke rises from the "+
		"fire to fill the air.");
	}
	return BSN(
		"Traces of smoke linger in the air.");

    default:	/* room long */
    	/* door open/closed desc will be appended to room */
	if (fire_state == FIRE_BURNING)
	{
	    return BSN("A large, dim shed. A fire burns steadily "+
		"in a pit in the center of the floor, and "+
		"bundles dangle in the gloom above.");
	}
    	return BSN("A large, dim shed. A fire pit is sunk in the center "+
	    "of the floor, and bundles dangle in the gloom above.");
    }
    return "";	/* "cannot" happen */
} /* fire_desc */
