/*
 * /d/Gondor/open/fireplace/fireplace_example.c
 *
 * Copyright (C) 1997 by Nancy L. Mintz (Gnadnar)
 *
 * an example room that uses the Gondor fireplace code
 *
 * see also: /d/Gondor/open/fireplace/fireplace.doc
 */

#pragma strict_types

inherit "/std/room";
inherit "/d/Gondor/open/fireplace/fireplace";

#include <stdproperties.h>
 
/*
 * do all your other #include's here.  it's important that the
 * #include of fireplace.h come last.  it #define's a lot of macros,
 * many of which are already defined in the defs.h of various domains.
 * since it checks before each #define, if it comes last, things will 
 * work fine.  if you include your domain files after it, things are 
 * likely to break.
 */
 
#include "/d/Gondor/open/fireplace/fireplace.h"

/* prototypes */
public void	create_room();
public void	reset_room();
public void	init();
public string	fire_desc(string arg);	/* VBFC for fire descriptions */

/* someone to tend the fire */
static object  Ranger;

/*
 * Function name:	create_room
 * Description	:	set up the room. 
 *			(this example just sets up the fireplace)
 */
public void
create_room() 
{
    set_short("a guardroom");
    set_long(fire_desc);	/* use VBFC for room description */

    /* set the pattern for parse_command() */
    set_parse_pattern("[the] [wide] [stone] 'fireplace'");

    /* use VBFC for all items that vary with the state of the fire.
     * notice that we pass an arg to fire_desc so we'll know which
     * item the player examined.
     */
    add_item( ({ "stone fireplace", "wide fireplace", 
	"wide stone fireplace", "fireplace" }), &fire_desc("fireplace"));
    add_item( ({ "fire", "flame", "flames" }), &fire_desc("fire"));

    /* add "... in fireplace" items so players may examine the wood/ashes 
     * in the fireplace even if they have wood/ashes in their inventory.
     */
    add_item( ({ "wood", "firewood", "wood in fireplace",
	         "firewood in fireplace" }),
	&fire_desc("wood"));
    add_item( ({ "ash", "ashes", "ash in fireplace",
	"ashes in fireplace" }),
	&fire_desc("ashes"));


    /* ... here you would add_item() things that don't vary with the fire,
     * add exits, clone up doors, etc etc
     */

    add_prop(ROOM_I_INSIDE, 1);
    reset_room();
} /* create_room */


/*
 * Function name:	reset_room
 * Description	:	create a ranger if needed, replenish
 *			the firewood and fire
 */
public void
reset_room()
{
    if (!objectp(Ranger))
    {
	setuid(); seteuid(getuid());
	Ranger = clone_object("/d/Gondor/common/npc/random_ranger");
	Ranger->move_living("away", TO);
    }

    /* reset wood to default amount */
    set_wood(-1);

    /* if fire's gone out and there's someone here to rekindle it,
     * start it up again.
     */
    if (query_fire_state() != FIRE_BURNING &&
	ENV(Ranger) == TO)
    {
	tell_room(TO,
	    BSN("The ranger tosses some fresh wood in the fireplace "+
		"and set it ablaze."));
	set_fire_state(FIRE_BURNING);
    }
} /* reset_room */


/*
 * Function name:	init
 * Description	:	call init_fire() to add fireplace verbs
 */
public void
init() 
{
    ::init();
    init_fire();
} /* init */


/*
 * Function name:	fire_desc
 * Descripiton	:	VBFC for room and items that vary w fire
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
	    return BSN("A wide stone fireplace is set into the north "+
		"wall. A fire burns brightly in the fireplace, "+
		"casting a flickering light over the room.");
	case FIRE_UNLIT_WOOD:
	    return BSN("A wide stone fireplace is set into the north "+
		"wall. Firewood is stacked in the fireplace.");
	default:	/* FIRE_ASHES */
	    return BSN("A wide stone fireplace is set into the north "+
		"wall.");
	}

    case "fire":
	if (fire_state == FIRE_BURNING)
	    return BSN("A fire burns brightly in the fireplace.");
	return BSN("You find no fire.");

    case "wood":
	switch (fire_state)
	{
	case FIRE_BURNING:
	    return BSN("The wood in the fireplace burns brightly, "+
		"emiting a pleasant warmth.");
	case FIRE_UNLIT_WOOD:
	   return BSN("Unlit wood is piled in the fireplace.");
	default:	/* FIRE_ASHES */
	    return BSN("You find no firewood.");
	}

    case "ashes":
	switch (fire_state)
	{
	case FIRE_BURNING:
	    return BSN("Beneath the brightly burning fire, "+
		"ashes cover the bottom of the fireplace.");
	case FIRE_UNLIT_WOOD:
	    return BSN("Beneath the wood, "+
		"ashes cover the bottom of the fireplace.");
	default:	/* FIRE_ASHES */
	    return BSN("Ashes cover the bottom of the fireplace.");
	}

    default:	/* room long description */
	if (fire_state == FIRE_BURNING)
	{
	    return BSN(
		"The guardroom is sparsely furnished and its walls are "+
		"bare, but the brightly burning fire adds some cheer.");
	}
	return BSN(
	    "The guardroom is sparsely furnished, its walls are "+
	    "bare, and there's a cold draft from the fireplace.");
    }
    return "";	/* "cannot" happen */
} /* fire_desc */
