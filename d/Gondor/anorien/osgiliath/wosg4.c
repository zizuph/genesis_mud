/*
 * /d/Gondor/anorien/osgiliath/wosg4.c
 *
 * Modification history:
 * 9 Oct 1998, Gnadnar: clean up, make desc of bridge
 *			vary with bridge state
 */


#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include "/d/Gondor/defs.h"

#define	BRIDGE_ROOM	(OSG_DIR+"wbridge1")

/* prototypes */
public void	create_area_room();
public void	reset_room();
public string	exa_ruins();


static object  Orc1, 
               Orc2, 
               Uruk;

/*
 * Function name:	create_area_room
 * Description	:	set up the room
 */
public void
create_area_room()
{
    FIX_EUID;	/* might try to load bridge room */
    set_areadesc("riverside in western Osgiliath");
    set_area("southern");
    set_areaname("Anorien");
    set_land("Gondor");
    set_grass("No");
    set_extraline("To the east flows the mighty River Anduin on its way "+
	"to the sea. Across the river you think you can see smoke rising "+
	"from a campfire but you're unable to see any beings there. The "+
	"muddy bank reveals some marks to you. North are the ruins of "+
	"Osgiliath.");

    add_exit((OSG_DIR + "wosg3"),     "north", 0, 2);
    add_exit((OSG_DIR + "wosg1"),     "west",  0, 2);
    add_exit((OSG_DIR + "boatplace"), "south", 0, 2);

    add_item( ({ "river", "anduin", "flood" }), BSN(
        "The mighty river Anduin flows southwards to the sea through most "+
	"of the north-eastern parts of Middle-earth. Here at Osgiliath it "+
	"is a broad and "+ "strong river, swift-flowing and unyielding to "+
	"its environments, save for the hills of Emyn Arnen around which "+
	"the river makes a wide turn further south of here. It looks too "+
	"strong to swim across."));
    add_item("marks",
	"The marks look like foot-prints - possibly from orcs!\n");
    add_item( ({ "osgiliath", "ruins", "bridge", }),
	exa_ruins);
    add_item("bank",
	"You find some marks in the muddy bank.\n");
    add_item("campfire", BSN(
	"It is a clumsy campfire, releasing far too much smoke for there "+
        "be the slightest hope of any secrecy about it."));

    reset_room();
} /* create_area_room */

/*
 * Function name:	reset_room
 * Description	:	replenish the orcs
 */
public void
reset_room()
{
    ::reset_room();

    Orc1 = clone_npc(Orc1, NPC_DIR + "reorc");
    Orc2 = clone_npc(Orc2, NPC_DIR + "reorc");
    Uruk = clone_npc(Uruk, NPC_DIR + "reuruk");
} /* reset_room */

/*
 * Function name:	exa_ruins
 * Description	:	VBFC for the ruins (bridge up or down?)
 * Returns	:	string -- the description
 */
public string
exa_ruins()
{
    BRIDGE_ROOM->short();
#if 0
    if (BRIDGE_ROOM->query_bridge_broken())
#else
    if (objectp(find_living("krug")))
#endif
    {
	return BSN(
            "To the north lie the ruins of Osgiliath. Between the hollow " +
            "shapes of burnt-out houses and towers, the first pier of a "+
	    "mighty bridge extends into the river. This one pier is all "+
	    "that remains of the bridge on this bank.");
    }
    return BSN(
        "To the north lie the ruins of Osgiliath. Between the hollow " +
        "shapes of burnt-out houses and towers, a mighty bridge "+
	"extends into the river.");
} /* exa_ruins */
