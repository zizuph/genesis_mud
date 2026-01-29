/*
 * /d/Gondor/ithilien/forest/ncamp.c
 *
 * Coded by Elessar.
 *
 * Modification log:
 * 30-Dec-1997, Gnadnar: general revision
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/room";

#include "/d/Gondor/defs.h"

public void
create_gondor()
{
    set_short("the northern edge of a camp in Ithilien");
    set_long(BSN(
	"Brutally slashed trees line this northern edge of "+
	"a forest clearing. "+
	"A large number of tents are visible to the south and "+
	"east, and a few campfires are burning lazily among "+
	"the tents. A well-trodden track leads north into the forest.")); 

    add_item( ({ "camp", "tent", "tents", "clearing" }), BSN(
	"The clearing stretches out south and east. A great number "+
	"of tents have been raised there."));
    add_item( ({ "ground", "track" }),
	"The track appears to have been made by hundreds of feet "+
	"trampling through the forest."); 
    add_item( ({ "trees", "tree", "forest" }), BSN(
	"Forest extends to the north and west around this clearing. "+
	"Along the edge of the clearing, the trees have been "+
	"slashed and burned, apparently with no thought for order "+
	"or beauty."));

    add_exit(ITH_DIR+"forest/orccamp2", "south");
    add_exit(ITH_DIR+"forest/ncamp2", "east");
    add_exit(ITH_DIR+"forest/orcpath1", "north");
}

