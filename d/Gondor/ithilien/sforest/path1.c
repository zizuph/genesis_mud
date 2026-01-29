/*
 *	/d/Gondor/ithilien/sforest/path1.c
 *
 *	Coded by Olorin.
 *
 *	Modification log:
 *	 6-Feb-1997, Olorin:	Changed inheritance,
 *				general revision.
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include "/d/Gondor/defs.h"

public void
create_area_room()
{
    string *herbs;

    set_areatype(7);
    set_areadesc("path");
    set_area("southern");
    set_areaname("Ithilien");
    set_land("Gondor");
    set_treetype("oak");
    set_extraline("You are underneath a tangled knot of thorns. Twisted " +
        "boughs, stooping to the ground, are overridden by a clambering " +
        "maze of old briars. Over you, the leaves and thorns of the " +
        "bushes form a dense roof. To the south is a small road. A " +
        "narrow path leads deeper into the thicket to the northeast.");
    add_item(({"bush","bushes","thicket","boughs","briars"}), BSN(
        "The thicket surrounds you almost everywhere. To the south is " +
        "an opening in the bushes, and to the northeast, there " +
        "is a narrow path leading through them. Overhead, intertwining " +
        "boughs and briars form a dense roof, transforming the small space " +
        "into a hollow hall."));
    add_item(({"road"}), BSN(
        "The small road is passing just outside of the thicket, running " +
        "from southeast to west."));
    add_item(({"forest"}), BSN(
        "The forest is all around you, the bushes blocking your view " +
        "in almost all directions."));
    add_item(({"path", "passage"}), BSN(
        "The narrow path is winding into the thicket to the northeast, " +
        "but it is impossible to see more than a few feet in that " +
        "direction."));

    add_exit(ITH_DIR + "sforest/path2",   "northeast", 0, 2);
    add_exit(ITH_DIR + "emyn-arnen/vrd1", "south",     0, 2);

    herbs = HERB_MASTER->query_herbs("forest");
    set_up_herbs( ({ ONE_OF_LIST(herbs), ONE_OF_LIST(herbs), 
		     ONE_OF_LIST(herbs), HERB_DIR + "red_pepper", }), 
		  ({ "ground","field","flowers","forest"}), 3);
}
