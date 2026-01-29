/*
 *	/d/Gondor/ithilien/sforest/path2.c
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
    set_areadesc("narrow path through a thicket");
    set_area("southern");
    set_areaname("Ithilien");
    set_land("Gondor");
    set_treetype("oak");
    set_extraline("You are underneath a tangled knot of thorns. Twisted " +
        "boughs, stooping to the ground, are overridden by a clambering " +
        "maze of old briars. Over you, the leaves and thorns of the " +
        "bushes form a dense roof. The narrow path continues east and " +
        "southwest.");
    add_item(({"bush","bushes","thicket","boughs","briars"}), BSN(
        "The thicket surrounds you everywhere. To the east and to " +
        "the southwest, the narrow path is winding through them. " +
        "Overhead, intertwining boughs and briars form a dense roof, " +
        "transforming the small space into a hollow hall."));
    add_item(({"forest"}), BSN(
        "The forest is all around you, the bushes blocking your view " +
        "in almost all directions."));
    add_item(({"path", "passage"}), BSN(
        "The narrow path is winding through the thicket. It continues " +
        "east and southwest, but in neither direction can one see " +
        "more than a few feet."));

    add_exit(ITH_DIR + "sforest/thicket4", "east",      0, 2, 1);
    add_exit(ITH_DIR + "sforest/path1",    "southwest", 0, 1, 0);

    herbs = HERB_MASTER->query_herbs("forest");
    set_up_herbs( ({ ONE_OF_LIST(herbs), ONE_OF_LIST(herbs), 
		     ONE_OF_LIST(herbs), HERB_DIR + "red_pepper", }), 
		  ({ "ground","field","flowers","forest"}), 3);
}
