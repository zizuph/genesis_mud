inherit "/d/Gondor/rohan/entwash/entwash";

#include "/d/Gondor/defs.h";

void
reset_room()
{
    set_searched(0);
}

void
create_swamp()
{
    reset_room();

    set_extra_long("Streams move silently through this area, flowing"
     + " in a northeasterly direction. The ground here is quite wet,"
     + " and all around are the sounds of tiny insects. There seems"
     + " to be some sort of large expanse opening up to the north.");

    add_item(({"expanse","large expanse"}), BSN(
        "It is unclear what lies in most directions, due to the mist"
      + " which covers these fens, yet you get the definite impression"
      + " that things open up dramatically to the north."));

    make_deadtree();

    add_exit(ENTWASH_DIR + "ent1a", "southwest");
    add_exit(ENTWASH_DIR + "ent1c", "north");
    add_exit(ENTWASH_DIR + "ent1d", "northeast");
}
