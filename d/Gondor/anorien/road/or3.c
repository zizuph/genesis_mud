/*
 *	/d/Gondor/anorien/road/or3.c
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
    set_areadesc("barren field");
    set_areatype(8);
    set_area("southern");
    set_areaname("Anorien");
    set_land("Gondor");
    set_grass("dry short");
    set_extraline("You are standing just outside the ruins of Osgiliath, the "+
        "former capital of Gondor. The city was built on both sides of the "+
        "great River Anduin, which flows by just on the other side of the "+
        "houses to the east. A road runs northwestwards from here, crossing "+
        "a little stream before continuing into Anorien, and another road "+
        "can be seen further south from here, going towards the great "+ 
        "north-eastern Gate of the Rammas Echor. To the east and southeast are the "+
        "ruins of Osgiliath.");
    
    add_exit(OSG_DIR + "wosg2",    "east",      0, 3);
    add_exit(OSG_DIR + "wosg1",    "southeast", 0, 3);
    add_exit(ANO_DIR + "road/or2", "northwest", 0, 3);

    add_item( ({ "river", "anduin", "great river", "river anduin" }), BSN(
        "The river is not far to the east. Its waters are flowing slowly " +
        "southwards to the Sea. The river is so wide that the other bank " +
        "can just barely been seen."));
    add_item( ({ "houses", "ruins", "osgiliath", }), BSN(
        "The ruins of the eastern parts of Osgiliath are between here and " +
        "the river. The houses have fallen into decay long years ago, their " +
        "roofs collapsed and the walls fell over."));
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

