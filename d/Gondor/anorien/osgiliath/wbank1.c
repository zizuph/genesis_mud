/*
 *	/d/Gondor/anorien/ithilien/wbank1.c
 *
 *	Coded by Elessar.
 *
 *	Modification log:
 *	 1-Feb-1997, Olorin:	Changed inheritance,
 *				General revision.
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include "/d/Gondor/defs.h"

static object *Orc = allocate(2),
               Uruk;

public void
create_area_room()
{
    string *herbs;

    set_areadesc("riverside in western Osgiliath");
    set_area("southern");
    set_areaname("Anorien");
    set_land("Gondor");
    set_grass("long, wet");
    set_extraline("To the east flows the mighty River Anduin on its way to the "+
        "sea. Across the river you think you can see smoke rising from a campfire "+
        "but you are unable to see any beings there. The muddy bank reveals some "+
        "marks to you. North are the ruins of Osgiliath, and a stone bridge can "+
        "be seen crossing the flood halfways.");
    add_exit(OSG_DIR + "boatplace", "north", 0, 2);
    add_item( ({ "river", "anduin", "flood", }), BSN(
        "The mighty river Anduin flows southwards to the sea through most of the "+
        "north-eastern parts of Middle-earth. Here at Osgiliath it is a broad and "+
        "strong river, swift-flowing and unyielding to its environments, save for "+
        "the hills of Emyn Arnen around which the river makes a wide turn further "+
        "south of here. It looks too strong to swim across."));
    add_item("marks", "The marks look like foot-prints - possibly from orcs!\n");
    add_item( ({ "osgiliath", "ruins", "bridge"}), BSN(
        "To the north, you can see the ruins of Osgiliath. Between the " +
        "hollow shapes of burnt-out houses and towers, you see " +
        "the first pier of a mighty bridge extending into the river. " +
        "This one pier is all that remains of the bridge on this bank, for it " +
        "has been broken in ages past. If you want to cross the Anduin, you will " +
        "have to look for a boat or a ferry."));
    add_item("bank","You find some marks in the muddy bank.\n");
    add_item("campfire", BSN("It is a clumsy campfire releasing far too much " +
        "smoke to even hope for some secrecy about it. You guess it was made " +
        "by orcs."));

    reset_room();

    herbs = HERB_MASTER->query_herbs( ({ "middle earth", "plain" }) );
    set_up_herbs( ({ ONE_OF_LIST(herbs), ONE_OF_LIST(herbs), 
		     ONE_OF_LIST(herbs) }),
		  ({ }), 4);
}

public void
reset_room()
{
    ::reset_room();

    clone_npcs(Orc, NPC_DIR + "reorc", -1.0);
    Uruk = clone_npc(Uruk, NPC_DIR + "reuruk");
}
