/*
 *	/d/Gondor/ithilien/sforest/thicket4.c
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

public int
blocked()
{
    write("Crawling through the thicket you discover a narrow " +
        "path through the bushes.\n");
    return 0;
}

public void
create_area_room()
{
    string *herbs;

    set_areatype(7);
    set_areadesc("dense thicket");
    set_area("southern");
    set_areaname("Ithilien");
    set_land("Gondor");
    set_treetype("oak");
    set_extraline("You are underneath a tangled knot of thorns. Twisted boughs, " +
    "stooping to the ground, are overridden by a clambering maze of " +
    "old briars. Over you, the leaves and thorns of the bushes form a " +
    "dense roof. The only exit seems to be northeast.");
    add_item(({"bush","bushes","thicket","boughs","briars"}), BSN(
    "The thicket surrounds you everywhere, only to the northeast, there " +
    "is a narrow path leading through the bushes. Overhead, intertwining " +
    "boughs and briars form a dense roof, transforming the small space " +
    "into a hollow hall. The bushes to the west look a little thinner " +
    "than those elsewhere."));
    add_item(({"path","passage"}), BSN(
    "The only way out of the thicket leads northeast. But it might also " +
    "be possible to crawl through the bushes to the west."));

    add_exit(ITH_DIR + "sforest/thicket1", "northeast", 0, 1, 0);
    add_exit(ITH_DIR + "sforest/path2",    "west",      blocked, 2, 1);

    herbs = HERB_MASTER->query_herbs("forest");
    set_up_herbs( ({ ONE_OF_LIST(herbs), ONE_OF_LIST(herbs), 
		     ONE_OF_LIST(herbs), HERB_DIR + "red_pepper", }), 
		  ({ "ground","field","flowers","forest"}), 3);
}

