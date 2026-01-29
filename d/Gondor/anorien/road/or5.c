#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include "/d/Gondor/defs.h"

#define BLACK_RIDER_ROOM	"/d/Gondor/morgul/blackrider"

public void
create_area_room()
{
    set_areadesc("dry, grassy field");
    set_areatype(8);
    set_area("southern");
    set_areaname("Anorien");
    set_land("Gondor");
    set_grass("dry, short");
    set_extraline("You are standing just outside the ruins of "
      + "Osgiliath, the former capital of Gondor. Just before you "
      + "to the northeast are the houses of the west end of Osgiliath, "
      + "the part of the city fashioned on the west banks of the River "
      + "Anduin, upon which the city was built. The houses are not too "
      + "destroyed here, although they have been unused for the last 60 "
      + "years or so. The road towards Minas Tirith starts here, and "
      + "leads southwest towards the North-eastern Gate of the Outer "
      + "Wall.");
    add_exit(ANO_DIR + "osgiliath/wosg1", "northeast", 0, 3);
    add_exit(ANO_DIR + "road/rroad8",     "east",      0, 3);
    add_exit(ANO_DIR + "road/or4",        "southwest", 0, 3);

    add_item( ({ "river", "anduin", "great river", "river anduin" }), BSN(
        "The river is not far to the east. Its waters are flowing slowly " +
        "southwards to the Sea. The river is so wide that the other bank " +
        "can just barely been seen."));
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

    FIX_EUID
    BLACK_RIDER_ROOM->load_me();
}

string
query_dir_to_gate()
{
    return "southwest";
}

