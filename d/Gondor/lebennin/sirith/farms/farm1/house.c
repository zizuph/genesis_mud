/*
 * /d/Gondor/lebennin/sirith/farms/farm1/house.c
 * farmhouse of large farmstead in southern lebennin
 *
 * Copyright (C) 1997 by Nancy L. Mintz (Gnadnar)
 * Finwe,May 2019: Removed hidden exits
 * 
 */

#pragma strict_types

#include <stdproperties.h>              /* for ROOM_I_LIGHT, etc*/
#include <ss_types.h>			/* for SS_AWARENESS	*/
#include "/d/Gondor/defs.h"
#include "../defs.h"
#include "/d/Gondor/open/fireplace/fireplace.h"

inherit "/d/Gondor/lebennin/sirith/room";
inherit "/d/Gondor/open/fireplace/fireplace";

static int	Scraps_here;		/* scraps in cupboard?		*/
static object	Raichim;		/* farmer			*/

public void	create_sirith();
public void	reset_room();
public void	init();
public string	do_search(object tp, string arg);	/* handle search */
public string	fire_desc(string arg);			/* VBFC for fire */
public string	swing_vane();				/* VBFC for vane */


/*
 * Function name:	create_sirith
 * Description	:	set up the room
 */
public void
create_sirith()
{
    set_short("a snug farmhouse");
    set_long(BSN("A snug farmhouse. "+
        "A deep fireplace with a raised hearth fills the north wall, "+
        "and a low cupboard stands beneath the west-facing window. "+
        "Baskets and bundles hang above the long table in the center of "+
        "the room."));
    /* door open/closed desc will be appended to room */

    add_prop(ROOM_I_LIGHT, 1);
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(OBJ_S_SEARCH_FUN, "do_search");
    add_prop(OBJ_I_SEARCH_TIME, 2);

    add_exit("hedgeyard", "east", 0, 2);
    set_door(SIRITH_FARMS_DIR + "obj/f1_house_door2");
    set_no_exit_msg( ({ "north", "northeast", "southeast",
	"south", "southwest", "west", "northwest", "up", "down" }),
	BSN("You wander around the room.") );

    add_item( ({ "farmhouse", "house" }),
	long);

    set_parse_pattern("[the] [stone] 'fireplace'");
    add_item( ({ "north wall", "stone fireplace", "fireplace" }),
	&fire_desc("fireplace"));
    add_item( ({ "fire" }),
	&fire_desc("fire"));
    add_item( ({ "wood", "firewood", "wood in fireplace",
		 "firewood in fireplace" }),
	&fire_desc("wood"));
    add_item( ({ "ash", "ashes" }),
	&fire_desc("ash"));

    add_item( ({ "stone", "stones", "river stone", "river stones" }),
	BSN("The fireplace is build of river stones, smooth and "+
	    "gently rounded."));
    add_item( ({ "raised hearth", "wide stone hearth",
		 "stone hearth", "hearth" }),
	BSN("The wide stone hearth is about the height of your knees."));
    add_item( ({ "metal vane", "hinged vane", "hook", "vane" }),
 	BSN("A metal vane has been securely fastened to the stones "+
	    "within the fireplace. The vane is hinged so that it can "+
	    "swing out from the hearth to be hung with a pot or kettle "+
	    "upon the long hook at its end. The hook is empty."));
    add_item( ({ "planks", "polished planks", "floor" }),
	BSN("Lightly polished planks are underfoot."));
    add_item( ({ "wall", "walls", "plaster" }),
	BSN("The plaster walls are smooth and clean."));
    add_item( ({ "ceiling" }),
	BSN("The ceiling seems to be used for storage. Baskets, "+
	    "bundles of vegetables, dried herbs and the like "+
	    "hang overhead."));
    add_item( ({ "basket", "baskets" }),
	BSN("Baskets of varying sizes hang overhead."));
    add_item( ({ "bundles", "bundles of vegetables", "vegetables", 
		 "dried herbs", "herbs", "provender" }),
	BSN("Bundles of vegetables, dried herbs and the like hang "+
	    "overhead. The ceiling seems to be the storage place for "+
	    "lightweight, non-perishable provender."));
    add_item( ({ "long table", "table" }),
	BSN("The table is easily long enough to seat eight; benches "+
	    "are pulled close beneath it."));
    add_item( ({ "bench", "benches" }),
	BSN("Plain wooden benches are pulled close to the table."));
    add_item( ({ "hedge", "grassy area", "grass", "area", "out window", 
		 "window" }),
	BSN("The small window overlooks a grassy area between the "+
	    "house and the hedge that encloses the farmyard."));
    add_item( ({ "low cupboard", "cupboard" }),
	BSN("The cupboard has storage space beneath a wooden top. "+
	    "It is low enough to fit beneath the window."));
    add_item( ({ "storage space", "space", "storage" }),
	BSN("Dishes, cooking utensils and the like are stored "+
	    "in the cupboard."));
    add_item( ({ "dish", "dishes", "cooking utensil",
		 "cooking utensils", "utensil", "utensils" }),
	BSN("The dishes and such are clearly used for preparing food."));
    add_item( ({ "cupboard top", "wooden top", "top", "surface", 
		 "work surface" }),
	BSN("The cupboard top is a well-scrubbed work surface."));

    add_cmd_item( ({ "benches", "on benches", "bench", "on bench", "down" }),
	({ "sit" }),
	BSN("You take a brief rest on one of the benches, then stand back "+
	    "up."));

    add_cmd_item( ({ "metal vane", "hinged vane", "hook", "vane" }),
	({ "move", "swing", "pull", "push" }),
	swing_vane);

    add_cmd_item( ({ "basket", "baskets", "bundles", "bundles of vegetables",
		     "vegetables", "dried herbs", "herbs", "provender",
		     "ceiling" }),
	({ "get", "take", "search" }),
	BSN("The items hanging from the ceiling are not within your reach."));
	/* XXX any reasonable soul will now try to climb/stand on table */

    reset_room();
} /* create_sirith */


/*
 * Function name:	reset_room
 * Description	:	restore scraps, npc and fire
 */
public void
reset_room()
{
    ::reset_room();
    Scraps_here = 1;

    Raichim = clone_npc(Raichim,
	      (SIRITH_FARMS_DIR+"npc/raichim"),
	      ({ (SIRITH_FARMS_DIR+"farm1"), (SIRITH_FARMS_DIR+"fields") }));

    set_wood(-1);
    if (query_fire_state() != FIRE_BURNING &&
	ENV(Raichim) == TO)
    {
	Raichim->command("emote puts some wood in the fireplace.");
	Raichim->command("emote lights the fire.");
	set_fire_state(FIRE_BURNING);
    }
} /* reset_room */


/*
 * Function name:	init
 * Description	:	add the fireplace verbs
 */
public void
init()
{
    ::init();
    init_fire();
} /* init */


/*
 * Function name:	do_search
 * Description	:	handle searching cupboard
 * Arguments	:	object tp	this player
 *		:	string		whatever the player searched
 * Return	:	msg to display to player
 */
public string
do_search(object tp, string arg)
{
    object	bowl,
		scraps;
    string	msg,
		where,
		what;

    seteuid(getuid());

    if (!strlen(arg))
    {
	return "";
    }

    if (sscanf(arg, "%s for %s", where, what) != 2)
    {
	where = arg;
    }

    if ((where != "dish" &&
	 where != "dishes" &&
         where != "cooking utensil" &&
	 where != "cupboard" &&
         where != "cooking utensils" &&
	 where != "utensil" &&
         where != "utensils" &&
	 where != "storage space" &&
         where != "storage" &&
	 where != "space") ||
        (strlen(what) &&
	 what != "scraps" &&
	 what != "bowl" &&
         what != "bowl of scraps"))
    {
	return "Your search reveals nothing special.\n";
    }

    if (!Scraps_here ||
        TP->query_skill(SS_AWARENESS) < (MIN_AWARE + random(RANDOM_AWARE)) ||
        !objectp(bowl = clone_object(SIRITH_FARMS_DIR+"obj/bowl")))
    {
	return BSN("You search the "+arg+
	           ", but do not find anything of interest.");
    }
    if (!objectp(scraps = clone_object(SIRITH_FARMS_DIR + "obj/scraps")))
    {
	bowl->remove_object();
	return BSN("You search the "+arg+
	           ", but do not find anything of interest.");
    }
    if (scraps->move(bowl))
    {
	scraps->remove_object();
	bowl->remove_object();
	return BSN("You search the "+arg+
	           ", but do not find anything of interest.");
    }

    Scraps_here = 0;
    msg = "In the very bottom of the cupboard, you find "+
	"a bowl of scraps.";
    if (bowl->move(TP))
    {
	bowl->move(TO);
	msg += "\nOops, you drop the bowl.";
    }
    return BSN(msg);
} /* do_search */


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
	    return BSN("The stone fireplace is quite large, with a "+
		"broad raised hearth. A fire is burning in the fireplace, "+
		"and a metal vane extends over the fire.");
	case FIRE_UNLIT_WOOD:
	    return BSN("The stone fireplace is quite large, with a "+
		"broad raised hearth. A metal vane extends over a small "+
		"pile of wood in the center of the fireplace.");
	default:	/* FIRE_ASHES */
	    return BSN("The stone fireplace is quite large, with a "+
		"broad raised hearth. A metal vane extends over the ashes "+
		"in the center of the fireplace.");
	}

    case "fire":
	if (fire_state == FIRE_BURNING)
	{
	    return BSN("A fire burns briskly in the fireplace, "+
		"casting a warm light over the room.");
	}
	return BSN("You find no fire.");

    case "wood":
	switch (fire_state)
	{
	case FIRE_BURNING:
	    return BSN("The wood in the fireplace burns briskly, casting "+
		"a warm light over the room.");
	case FIRE_UNLIT_WOOD:
	   return BSN("Unlit wood is piled in the fireplace.");
	default:	/* FIRE_ASHES */
	    return BSN("You find no "+Exa_arg+".");
	}

    case "ash":
	switch (fire_state)
	{
	case FIRE_BURNING:
	    return BSN("Beneath the briskly burning fire, "+
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


/*
 * Function name:	swing_vane
 * Description	:	handle attempts to mess with fireplace vane
 * Returns	:	string describing the results
 * 
 * XXX can "extinguish fire" and then immediately "swing vane" -- 
 * not quite realistic. to do this properly, would set an alarm
 * to cool the vane down some time after the fire was extinguished.
 */
public string
swing_vane()
{
    if (query_fire_state() == FIRE_BURNING)
    {
	return "The metal vane is too hot to touch.\n";
    }
    SAY(" swings the metal vane in the fireplace back and forth.\n");
    return "You swing the metal vane back and forth.\n";
} /* swing_vane */
