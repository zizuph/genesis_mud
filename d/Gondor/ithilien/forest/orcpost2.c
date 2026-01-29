/*
 * /d/Gondor/ithilien/forest/orcpost2.c
 *
 * Coded by Elessar.
 *
 * Modification log:
 *  4-Feb-1997, Olorin:	General revision.
 * 30-Dec-1997, Gnadnar:	inherit camp.c
 */

#pragma strict_types

inherit "/d/Gondor/ithilien/forest/camp";

#include "/d/Gondor/defs.h"

static object	*Orc = allocate(4),
		Uruk;
public int      cross_palisades();

public void
create_camp()
{
    set_short("inside a palisade in the Ithilien Forest");
    set_long("You are standing inside a primitive palisade constructed "+
	"from a few logs placed between two piles of rocks. "+
	"In the clearing to the east, tents encircle a campfire. "+
	"Many trees have been mutilated and cut down for firewood. "+
	"A foul smell permeates the area, and a pile of refuse lies "+
	"to the north.\n");

    add_item( ({ "pile of refuse", "garbage", "refuse" }), 
	   "There is a pile of rancid refuse to the north.\n");
    add_item( ({ "clearing", "fire", "fires", "campfire", "campfires" }),
	   "A few campfires burn in the clearing to the east. "+
	   "Shapes move among tents around the fires.\n");
    add_item( ({ "tent", "tents" }), 
	   "There are a few tents in the clearing to the east.\n");
    add_item( ({ "wall", "palisade", "barricade" }), 
	   "A palisade has been built to protect against assaults "+
	   "from the riverside. It is quite primitive and small.\n");
    add_item( ({ "tree trunks", "trunks", "logs", "piles of rocks",
	   "rocks", "piles" }), 
	   "Two piles of rocks have been raised, and a few tree trunks placed "+
	   "as a wall between the piles, like a primitive palisade.\n");
    add_item(({"tree","trees"}), 
	   "There are hardly any trees left here; most have apparently " +
	   "been cut down for firewood. The ones that are still standing " +
	   "have been mutilated wantonly, their bark in many places ruined, " +
	   "branches hewn off, the stems smeared with dirt. \n");

    add_exit(ITH_DIR + "forest/orccamp1",  "east",  check_allow, 1);
    add_exit(ITH_DIR + "forest/orcpost",   "west",  cross_palisades, 1);
    add_exit(ITH_DIR + "forest/orcrefuse", "north", 0, 1);

    reset_room();

    add_orc_camp_tells();
}

public void
reset_room()
{
    ::reset_room();
    clone_npcs(Orc, NPC_DIR + "reorc", 5.0);
    Uruk = clone_npc(Uruk, NPC_DIR + "reuruk");
}

public int
cross_palisades()
{
    write("You climb over the palisades.\n");
    return 0;
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
    {
        start_room_tells();
    }
}
