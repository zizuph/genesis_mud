/*
 * /d/Gondor/ithilien/forest/orccamp2.c
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

static object *Orc = allocate(2);

public void
create_camp()
{
    set_short("a part of the orc camp in Ithilien");
    set_long("Tents fill this north end of the "+
	"clearing. The forest surrounding the camp is green and beautiful, "+
	"but a foul smell from the west disturbs the beauty. South is a campfire, "+
	"and still more tents.\n");
    add_item( ({ "tent", "tents" }), 
	"The tents, made of greyish canvas, are large and well-kept.\n");
    add_item( ({ "trees", "oaks", "larches", "woods", "forest" }), 
	"The forests of Ithilien are all green and lovely. "+
	"Oaks and larches appear to be the dominant trees.\n");
    add_item( ({ "fire", "campfire" }), 
	"There is a campfire to the south of here.\n");

    add_exit(ITH_DIR + "forest/ncamp",      "north", 0, 1);
    add_exit(ITH_DIR + "forest/haradcamp1", "east",  0, 1);
    add_exit(ITH_DIR + "forest/orcrefuse",  "west",  0, 1);
    add_exit(ITH_DIR + "forest/orccamp1",   "south", check_allow, 1);

    reset_room();

    add_orc_camp_tells();
}

public void
reset_room()
{
    clone_npcs(Orc, NPC_DIR + "reorc", -1.0);
}
