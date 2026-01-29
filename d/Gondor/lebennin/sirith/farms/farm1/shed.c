/*
 * /d/Gondor/lebennin/sirith/farms/farm1/shed.c
 * shed on large farmstead in southern lebennin
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

static object	Sandros;		/* the hired farmhand	*/


/*
 * Function name:	create_sirith
 * Description	:	set up the room
 */
public void
create_sirith()
{
    set_short("a tiny shed");
    set_long(fire_desc);

    add_exit("westyard", "east", 0, 2);
    set_no_exit_msg( ({ "north", "northeast", "southeast",
	"south", "southwest", "west", "northwest", "up", "down" }),
	BSN("You try to walk around the shed, but there is not much "+
	    "room to move.") );

    add_prop(ROOM_I_LIGHT, 1);
    add_prop(ROOM_I_INSIDE, 1);

    set_fire_container("fire pit");
    /* this will match "the fire firepit", but it's probably worth
     * it in order to match either "the pit" or "the fire pit" or 
     * "the firepit"
     */
    set_parse_pattern("[the] [fire] 'pit' / 'firepit'");
    add_item( ({ "firepit", "fire pit", "pit" }),
	&fire_desc("fire pit"));
    add_item( ({ "fire" }),
	&fire_desc("fire"));
    add_item( ({ "wood", "firewood", "wood in firepit",
		 "firewood in firepit", "wood in fire pit",
		 "firewood in fire pit" }),
	&fire_desc("wood"));
    add_item( ({ "ash", "ashes" }),
	&fire_desc("ash"));

    /* don't think a fire pit is "furnishings" :-) */
    add_item( ({ "furnishings" }),
	BSN("Except for the pallet and stool, the shed is bare."));
    add_item( ({ "pallet", "blanket", "straw", "pad", "straw pad" }),
	BSN("The pallet is a skimpy straw pad covered "+
	    "by a dirty blanket."));
    add_item( ({ "stool" }),
	BSN("A short, three-legged stool. It doesn't look very "+
	    "comfortable."));
    add_item( ({ "stone", "stones" }),
	BSN("Blackened stones line the fire pit."));
    add_item( ({ "floor", "dirt" }),
	BSN("The floor is bare, packed dirt around a small fire pit."));
    add_item( ({ "wall", "walls", "plank", "planks" }),
	BSN("The walls are bare, splintery planks."));
    add_item( ({ "air", "smoke" }),
	BSN("The air is quite smoky."));
    add_item( ({ "ceiling", "hole" }),
	BSN("The ceiling is fairly low and blackened by smoke. A hole in "+
	    "the center of the ceiling probably is intended to vent smoke "+
	    "from the fire, but it evidently is not very effective."));

    add_cmd_item( ({ "stool", "on stool", "down" }), ({ "sit" }),
	BSN("As you place your weight on the stool, it wobbles "+
	    "alarmingly. You quickly stand back up."));
    add_cmd_item( ({ "smoke", "air" }), ({ "smell", "sniff", "inhale" }),
	BSN("The smoke has a slightly sweet aroma."));
    add_cmd_item( ({ "down on blanket", "on blanket", "down on pad",
	"on pad", "down on pallet", "down", "on pallet" }),
	({ "lie" }),
	BSN("You cannot bring yourself to lie on the dirty blanket."));

    reset_room();
} /* create_sirith */


/*
 * Function name:	reset_room
 * Description	:	replenish npc, wood, fire
 */
public void
reset_room()
{
    ::reset_room();

    Sandros = clone_npc(Sandros,
	     (SIRITH_FARMS_DIR+"npc/sandros"),
	     ({ (SIRITH_FARMS_DIR+"farm1"), (SIRITH_FARMS_DIR+"fields") }));

    set_wood(-1);
    if (query_fire_state() != FIRE_BURNING &&
	ENV(Sandros) == TO)
    {
	Sandros->command("emote tosses some wood into the fireplace.");
	Sandros->command("emote lights the fire.");
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
		"The fire pit is just a stone-lined depression in "+
		"the center of the floor. A smoky fire burns fitfully "+
		"in the pit.");
	case FIRE_UNLIT_WOOD:
	    return BSN(
		"The fire pit is just a stone-lined depression in "+
		"the center of the floor. Firewood is piled in the pit.");
	default:	/* FIRE_ASHES */
	    return BSN(
		"The fire pit is just a stone-lined depression in "+
		"the center of the floor, holding nothing but ashes.");
	}

    case "fire":
	if (fire_state == FIRE_BURNING)
	{
	    return BSN(
		"A fire burns fitfully in the fire pit, "+
		"emitting more smoke than heat or light.");
	}
	return "You find no fire.\n";

    case "wood":
	switch (fire_state)
	{
	case FIRE_BURNING:
	    return BSN(
		"The wood in the fire pit burns very low and "+
		"gives off a lot of smoke.");
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

    default:	/* room long */
	if (fire_state == FIRE_BURNING)
	{
    	    return BSN("A tiny shed. The only furnishings are a pallet "+
		"and a low stool. A smoky fire burns in a pit in the "+
		"center of the floor.");
	}
    	return BSN("A tiny shed. The only furnishings are a pallet "+
		"and a low stool. A fire pit occupies the center of "+
		"the floor, and the air is rather smoky.");
    }
    return "";	/* "cannot" happen */
} /* fire_desc */
