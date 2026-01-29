#include "defs.h"

inherit SHRINEBASE;

public void
create_room()
{
    set_long("You have reached the southmost end of a small " +
        "building of some sort. There are no more clues here than " +
        "there were in the north part of the building as to what " +
        "its purpose might have been. Some sort of food storage, " +
        "maybe? Regardless, the construction methods are virtually " +
        "identical here to those of the north part of the building. " +
        "Apparently a large stone slab was laid across the top of " +
        "three vertical stone slabs of a strange, dark-coloured " +
        "stone.\n\n");


    create_shrine();
    remove_prop("archway");

    add_exit(FOREST + "shrine_1", "north");
}
