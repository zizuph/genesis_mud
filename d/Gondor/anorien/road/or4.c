/*
 *	/d/Gondor/anorien/road/or4.c
 *
 *	Coded by Elessar.
 *
 *	Modification log:
 *	 3-Feb-1997, Olorin:	Changed inheritance,
 *				general revision.
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include "/d/Gondor/defs.h"

public void
create_area_room()
{
    set_areadesc("dry, grassy field");
    set_areatype(8);
    set_area("southern");
    set_areaname("Anorien");
    set_land("Gondor");
    set_grass("dry, short");
    set_extraline("The road leads northeast towards Osgiliath and " +
        "southwest towards the northeastern gate of the Rammas Echor. " +
        "The gentle sound of the flowing waters of the great River " +
        "can be heard from the east. Further northeast are the ruins " +
	"of Osgiliath.");

    add_exit(ANO_DIR + "road/or5",  "northeast", 0, 3);
    add_exit(PEL_DIR + "neoutgate", "southwest", 0, 3);

    add_item( ({ "river", "anduin", "great river", "river anduin" }), BSN(
        "The river Anduin is not visible from here, but the sound of " +
        "its waters flowing southwards can be heard not far to the east."));
    add_item( ({ "ruins", "osgiliath", }), BSN(
        "The ruins of the eastern parts of Osgiliath are visible to " +
        "the northeast. It is hard to make out details from here, save " +
        "that all the buildings are completely destroyed and only little " +
        "remains of them now."));
    add_item( ({ "gate", "rammas", "rammas echor", "wall", }), BSN(
        "The Rammas Echor is the great outer wall of Minas Tirith, " +
        "encircling all of the Pelennor. The northeastern gate, that " +
        "guards the road leading to Osgiliath, is to the southwest."));
}

string
query_dir_to_gate()
{
    return "southwest";
}

