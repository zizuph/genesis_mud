/*
 * /d/Gondor/lebennin/sirith/farms/farm2/house.c
 * house for small farmstead in southern lebennin
 *
 * Copyright (C) 1997 by Nancy L. Mintz (Gnadnar)
 *
 * XXX probably farm2 should have its own stack of firewood somewhere
 *
 */

#pragma strict_types

#include <stdproperties.h>	/* for ROOM_I_INSIDE, ROOM_I_LIGHT, etc	*/
#include <language.h>		/* for LANG_ADDART 			*/
#include "/d/Gondor/defs.h"
#include "../defs.h"			
#include "/d/Gondor/open/fireplace/fireplace.h"	/* for FIRE_*		*/

inherit "/d/Gondor/lebennin/sirith/room";
inherit "/d/Gondor/open/fireplace/fireplace";

static int	Tunic_here = 1;			/* tunic on peg?	*/
static object	Druyan;				/* the sheep farmer	*/

public void	create_sirith();
public void	reset_room();
public void	init();
public int	get_tunic();		/* to get tunic from the peg	*/
public string	fire_desc(string arg);		/* VBFC for fire 	*/


/*
 * Function name:	create_sirith
 * Description	:	set up room
 */
public void
create_sirith()
{
    set_short("a small farmhouse");
    set_long(BSN("A small farmhouse. A table, flanked by a "+
	"wooden bench, fills most of the room, leaving just "+
	"enough space for a chair by the fireplace. "+
	"Drawn curtains shroud a bed in the corner."));
	/* door open/close desc will be appended */

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 1);

    add_exit("westyard", "north", 0, 2, 1);
    set_door(SIRITH_FARMS_DIR + "obj/f2_house_door2");
    set_no_exit_msg( ({ "northeast", "east", "southeast",
	"south", "southwest", "west", "northwest", "up", "down" }),
	BSN("You wander around the room.") );

    set_parse_pattern("[the] [stone] 'fireplace'");
    add_item( ({ "southeast corner", "stone fireplace", "fireplace"  }),
	&fire_desc("fireplace"));
    add_item( ({ "fire" }),
	&fire_desc("fire"));
    add_item( ({ "wood", "firewood", "wood in fireplace",
		 "firewood in fireplace" }),
	&fire_desc("wood"));
    add_item( ({ "ash", "ashes" }),
	&fire_desc("ash"));

    add_item( ({ "farmhouse", "house" }), long);
    add_item( ({ "surface", "table", "scars" }),
	BSN("The surface of the table shows the scars of hard use."));
    add_item( ({ "bench" }),
	BSN("The bench is very plain and doesn't look comfortable."));
    add_item( ({ "floor" }),
	BSN("Broad unvarnished planks, closely fitted together."));
    add_item( ({ "ceiling" }),
	BSN("The ceiling is fairly close overhead."));
    add_item( ({ "chair" }),
	BSN("The chair is crudely carved, but looks comfortable enough."));
    add_item( ({ "corner", "corners" }),
	BSN("A stone fireplace is set into the southeast corner of the "+
	    "room, and a curtained bed occupies the southwest corner."));
    add_item( ({ "stone", "stones" }),
	BSN("The fireplace is built of smooth gray and brown stones, "+
	    "fitted tightly together."));

    add_item( ({ "confined niche", "southwest corner", "niche", "bed" }),
	BSN("The bed, set into a confined niche in the wall, is "+
	    "separated from the rest of the room by drawn curtains."));
    add_item( ({ "curtains", "curtain", "bed curtain", "bed curtains" }),
	BSN("Thick curtains close the bed off from the rest of the room."));


    add_cmd_item( ({ "on bench", "down" }),
	({ "sit" }),
	BSN("You sit briefly on the backless bench; it is decidedly "+
	    "uncomfortable, and you quickly stand up."));
    add_cmd_item( ({ "in chair", "on chair" }),
	({ "sit" }),
	BSN("You take a rest in the chair before the fireplace, then "+
	    "stand back up."));
    add_cmd_item( ({ "curtain", "curtains", "bed curtain", "bed curtains" }),
	({ "close" }),
	BSN("The bed curtains already are closed."));
    add_cmd_item( ({ "curtain", "curtains", "bed", "niche", 
		     "confined niche", "bed curtain", "bed curtains" }),
	({ "draw", "open", "search" }),
	BSN("You open the bed curtains and find only a simple "+
	    "bed, covered with a well worn blanket and topped with "+
	    "a hard pillow. You close the curtains again."));
    add_cmd_item( ({ "on bed",  "in bed" }),
	({ "sleep", "rest", "nap" }),
	BSN("You open the bed curtains and lie on the bed, only to "+
	    "discover that the straw-filled mattress is thin, "+
	    "prickly and not very comfortable. You stand up and "+
	    "close the curtains again."));
    add_cmd_item( ({ "on bed", "in bed", "down" }),
	({ "lie" }),
	BSN("You open the bed curtains and lie on the bed, only to "+
	    "discover that the straw-filled mattress is thin, "+
	    "prickly and not very comfortable. You stand up and "+
	    "close the curtains again."));

    reset_room();
} /* create_sirith */


/*
 * Function name:	reset_room
 * Description	:	replenish npc, wood, fire, tunic
 */
public void
reset_room()
{
    ::reset_room();

    Druyan = clone_npc(Druyan,
	               (SIRITH_FARMS_DIR+"npc/druyan"),
	     	       ({ (SIRITH_FARMS_DIR+"farm2"),
			  (SIRITH_FARMS_DIR+"fields") }));

    set_wood(-1);
    if (query_fire_state() != FIRE_BURNING &&
	ENV(Druyan) == TO)
    {
	Druyan->command("emote tosses some wood into the fireplace.");
	Druyan->command("emote lights the fire.");
	set_fire_state(FIRE_BURNING);
    }

    Tunic_here = 1;
    remove_item("wall");
    remove_item("walls");
    remove_item("wooden peg");
    remove_item("wooden pegs");
    remove_item("peg");
    remove_item("pegs"),
    remove_item("tunic on wooden peg");
    remove_item("tunic on peg");
    remove_item("tunic");
    remove_cmd_item("tunic from wooden peg");
    remove_cmd_item("tunic from peg");
    remove_cmd_item("tunic");
    add_item( ({ "tunic on wooden peg", "tunic on peg", "tunic" }), 
	BSN("A tunic hangs on one of the pegs near the door."));
    add_item( ({ "wall", "walls" }),
	BSN("The walls are bare, except for a row of "+
	   "pegs near the door. A tunic hangs on one of "+
	   "the pegs."));
    add_item( ({ "wooden peg", "wooden pegs", "peg", "pegs" }),
	BSN("The pegs are about head-high. A tunic hangs "+
	    "on one of the pegs; the rest are empty."));
    add_cmd_item( ({ "tunic from wooden peg", "tunic from peg", "tunic" }),
	({ "get", "take" }), get_tunic);
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
 * Function name:	get_tunic
 * Description	:	handle getting tunic from peg 
 * Returns	:	1 if succeeds, 0 otherwise
 */
public int
get_tunic()
{
    object	tunic;

    remove_item("wall");
    remove_item("walls");
    remove_item("wooden peg");
    remove_item("wooden pegs");
    remove_item("peg");
    remove_item("pegs"),
    remove_item("tunic on wooden peg");
    remove_item("tunic on peg");
    remove_item("tunic");
    remove_cmd_item("tunic from wooden peg");
    remove_cmd_item("tunic from peg");
    remove_cmd_item("tunic");
    add_item( ({ "wall", "walls" }),
	BSN("The walls are bare, except for a row of empty "+
	   "pegs near the door."));
    add_item( ({ "wooden peg", "wooden pegs", "peg", "pegs" }),
	BSN("The pegs are about head-high. They are empty."));
 
    if (Tunic_here &&
        objectp(tunic = clone_object(ARM_DIR + "tunic")))
    {
	DEBUG_LOG(TP->query_real_name()+" took the tunic!\n");
	Tunic_here = 0;
	write("You take the tunic from the peg.\n");
	SAY(" takes a tunic from the wall.");
	if (tunic->move(TP))
	{
	   write("Oops, you dropped it.\n");
	   SAY(" drops the tunic.");
	   tunic->move(TO);
	}
	return 1;
    } 
    /* "cannot" happen */
    NFN0(capitalize(query_verb())+" what?\n");
} /* get_tunic */


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

    case "fireplace":
	switch (fire_state)
	{
	case FIRE_BURNING:
	    return BSN(
		"A stone fireplace is set into the southeast corner "+
		"of the room. A fire burns steadily in the fireplace.");
	case FIRE_UNLIT_WOOD:
	    return BSN(
		"A stone fireplace is set into the southeast corner "+
		"of the room. Firewood is stacked in the fireplace.");
	default:	/* FIRE_ASHES */
	    return BSN(
		"A stone fireplace is set into the southeast corner "+
		"of the room.");
	}

    case "fire":
	if (fire_state == FIRE_BURNING)
	{
	    return BSN("A fire burns steadily in the fireplace.");
	}
	return "You find no fire.\n";

    case "wood":
	switch (fire_state)
	{
	case FIRE_BURNING:
	    return BSN("The wood in the fireplace burns steadily, giving "+
		"a pleasant warmth.");
	case FIRE_UNLIT_WOOD:
	   return BSN("Unlit wood is piled in the fireplace.");
	default:	/* FIRE_ASHES */
	    return "You find no "+Exa_arg+".\n";
	}

    case "ash":
	switch (fire_state)
	{
	case FIRE_BURNING:
	    return BSN("Beneath the steadily burning fire, "+
		"ashes cover the bottom of the fireplace.");
	case FIRE_UNLIT_WOOD:
	    return BSN("Beneath the unlit wood, "+
		"ashes cover the bottom of the fireplace.");
	default:	/* FIRE_ASHES */
	    return BSN("Ashes cover the bottom of the fireplace.");
	}
    }
    return "";	/* "cannot" happen */
} /* fire_desc */
