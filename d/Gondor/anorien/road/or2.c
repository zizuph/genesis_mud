/*
 *	/d/Gondor/anorien/road/or2.c
 *
 *	Coded by Elessar.
 *
 *	Modification log:
 *	 3-Feb-1997, Olorin:	Changed inheritance,
 *				general revision.
 *
 *  Added exits for Anorien plains - Varian 2016
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include "/d/Gondor/defs.h"

public void
create_area_room()
{
    set_areadesc("green, grassy field");
    set_areatype(8);
    set_area("southern");
    set_areaname("Anorien");
    set_land("Gondor");
    set_grass("long, dark green");
    set_extraline("The road continues west, while it crosses a little bridge "+
        "to the southeast. Not far away to the east you see the great river "+
        "Anduin, and the ruins of the old town Osgiliath, the previous "+
        "capital of Gondor, built on both sides of Anduin. You can see "+
        "a long stone-bridge stretching across the water within the ruins, "+
        "and some ruined buildings on an isle in the centre of the river.");

    add_exit(ANO_DIR + "road/or3",  "southeast", 0, 3);
    add_exit(ANO_DIR + "road/or1",  "west",      0, 3);
    add_exit(ANO_DIR + "plains/an16w11n","northeast",0,3,1);
    add_exit(ANO_DIR + "plains/an15w11n","north",0,3,1);
    add_exit(ANO_DIR + "plains/an14w11n","northwest",0,3,1);

    set_no_exit_msg(({"southwest","south"}),
        "You attempt to walk through the Rammas Echor, but you " +
        "notice the wall is far too solid for you to do that.\n");
    set_no_exit_msg(({"east"}),
        "You cannot enter Osgiliath this way, but the road which " +
        "runs southeast over the bridge will take you inside.\n");

    add_item( ({ "river", "anduin", "great river", "river anduin" }), BSN(
        "The river is not far to the east. Its waters are flowing slowly " +
        "southwards to the Sea. The river is so wide that the other bank " +
        "can just barely been seen."));
    add_item( ({ "ruins", "osgiliath", }), BSN(
        "The ruins of the eastern parts of Osgiliath are visible to " +
        "the east. It is hard to make out details from here, save " +
        "that all the buildings are completely destroyed and only little " +
        "remains of them now."));
    add_item( ({ "gate", "rammas", "rammas echor", "wall", }), BSN(
        "The Rammas Echor is the great outer wall of Minas Tirith, " +
        "encircling all of the Pelennor. The northeastern gate, that " +
        "guards the road leading to Osgiliath, is to the southwest."));
    add_item( ({ "island", "bridge", }), BSN(
        "In the middle of the river there is an island covered with " +
        "ruins. To both sides of the island mighty piers are standing " +
        "in the river, supporting a bridge. From here you cannot make " +
        "out of the bridge has fallen into ruins like the rest of " +
        "Osgiliath or if it is still possible to use it to cross the " +
        "river."));
}

string
query_dir_to_gate()
{
    return "southeast";
}

/*
 This was used while the plains were under construction. Now open
 Varian - August 2016

int
block()
{
    if (this_player()->query_wiz_level()) return 0;

    write("You should be able to enter the plains of Anorien soon!\n");
    return 1;
}

*/