/*
 * /d/Gondor/common/guild/north/great_hall.c
 *
 * Revision history:
 *	10-Dec-1997, Gnadnar:	general clean up and
 *				add working fireplace
 */

#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/std/room";
inherit "/d/Gondor/open/fireplace/fireplace";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/open/fireplace/fireplace.h"

object Mranger;

public string	fire_desc(string arg);	/* VBFC for fire */


/*
 * Function name:	create_gondor
 * Description	:	set up the room
 */
public void
create_gondor()
{
    set_short("the great hall");
    set_long(fire_desc);

    set_parse_pattern("[the] [deep] [stone] 'fireplace'");

    add_item( ({ "deep fireplace", "stone fireplace",
	"deep stone fireplace", "fireplace" }), &fire_desc("fireplace"));
    add_item( ({ "flames", "flame", "fire" }), &fire_desc("fire"));

    /* add "... in fireplace" items so players may examine the wood/ashes 
     * in the fireplace even if they have wood/ashes in their inventory.
     */
    add_item( ({ "wood", "firewood", "wood in fireplace",
	         "firewood in fireplace" }),
	&fire_desc("wood"));
    add_item( ({ "ash", "ashes", "ash in fireplace", "ashes in fireplace" }),
	&fire_desc("ashes"));

    add_item( ({ "mantel", "mantelpiece" }), BSN(
	"A mantelpiece of carved oak stetches the width of the fireplace."));
    add_item("banner", BSN(
	"The banner of the Dunedain displays the white tree surrounded "+
	"by seven stars."));
    add_item( ({ "tapestry", "tapestries" }), BSN(
	"The tapestries show Elendil, the first king of Arnor, and his "+
	"two sons, Isildur and Anarion. The most prominent one portrays "+
	"Elendil and his ships as they are washed ashore at Lindon. "+
	"Later he travelled up the river Lhun and established the realm "+
	"of Arnor."));
    add_item( ({ "stone pillars", "stone pillar", "large stone pillars",
	"large stone pillar", "large pillars", "large pillar",
    	"pillars", "pillar", "ceiling" }), BSN(
	"Large pillars of smooth stone support the ceiling."));
    add_item( ({ "stone floor", "floor", "ground" }), BSN(
	"The stone floor is softened by a thick rug."));
    add_item( ({ "thick rug", "rug" }), BSN(
	"The rug, of a rich wine colour, is soft and thick."));
    add_item( ({ "wall", "walls" }), BSN(
	"The walls, built of the same smooth stone as the pillar, are "+
	"pierced by low archways."));
    add_item( ({ "flecks", "smooth stone", "stone" }), BSN(
	"The stone is deep gray in colour, with flecks of silver and gold."));
    add_item( ({ "graceful archway", "graceful archways", "archway",
	"archways", "corridor", "corridors" }), BSN(
	"Beyond the archways, corridors lead in all directions."));

    add_prop(ROOM_I_INSIDE, 1);
    add_exit(RANGER_NORTH_DIR+"s_corridor","west",0);
    add_exit(RANGER_NORTH_DIR+"e_corridor","north",0);
    add_exit(RANGER_NORTH_DIR+"o_corridor","south",0);
    add_exit(RANGER_NORTH_DIR+"t_corridor","east",0);

    reset_room();
}


/*
 * Function name:	reset_room
 * Description	:	restore Halbarad and the fire
 */
public void
reset_room()
{
    if ( !objectp(Mranger) )
        Mranger = clone_npc(Mranger, RANGER_NORTH_DIR+"npc/halbarad");
    set_wood(-1);	/* replenish wood */
    if ( query_fire_state() != FIRE_BURNING && ENV(Mranger) == TO )
    {
	Mranger->command("emote places some wood in the fireplace.");
	Mranger->command("emote lights the wood.");
	set_fire_state(FIRE_BURNING);
    }
}

/*
 * Function name:	init
 * Description	:	add verbs for fire
 */
public void
init()
{
    ::init();
    init_fire();
}


/*
 * Function name:	fire_desc
 * Descripiton	:	VBFC for room and items that vary w fire
 * Arguments	:	string arg -- what we're looking at
 * Returns	:	string description
 */
public string
fire_desc(string arg)
{
    int		fire_state = query_fire_state();
    string	tmpstr;

    switch ( arg )
    {

    case "fireplace":
	switch ( fire_state )
	{
	case FIRE_BURNING:
	     return BSN( "The fireplace is built of the same dark gray "+
		"stone as the walls; the gold and silver flecks in the "+
		"stone sparkle in the light of the fire.");
	case FIRE_UNLIT_WOOD:
	     return BSN( "The fireplace is built of the same dark gray "+
		"stone as the walls. Wood is stacked in the fireplace, "+
		"ready to be lit.");
	default:	/* FIRE_ASHES */
	     return BSN( "The fireplace is built of the same dark gray "+
		"stone as the walls.");
	}

    case "fire":
	if ( fire_state == FIRE_BURNING )
	{
	    return BSN(
		({
		"The flickering gold and red flames are mesmerizing.",
		"The fire casts a warm light over the great hall.",
		"The fire burns brightly, imparting a warm glow "+
		    "to the surrounding stone."
		})[random(3)] );

	}
	return BSN("You find no fire.");

    case "wood":
	switch ( fire_state )
	{
	case FIRE_BURNING:
	    return BSN("The wood in the fireplace burns brightly, emiting "+
		"a pleasant warmth.");
	case FIRE_UNLIT_WOOD:
	   return BSN("Unlit wood is piled in the fireplace.");
	default:	/* FIRE_ASHES */
	    return BSN("You find no firewood.");
	}

    case "ashes":
	switch ( fire_state )
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

    default:	/* room description */
	if ( fire_state == FIRE_BURNING )
	    tmpstr = ", where a flickering fire casts a warm glow "+
		     "over the room. ";
	else
	    tmpstr = ". ";

        return BSN(
	    "The great hall of the northern headquarters is warm and "+
	    "commodious.  Two rows of large stone pillars support the high "+
	    "ceiling, rich tapestries cover the walls, and a grand banner "+
	    "hangs above a deep fireplace"+tmpstr+
	    "Graceful archways lead out of the hall.");
    }
    /* NOTREACHED */
}
