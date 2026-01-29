/*
 * The valley of the Barrow Downs
 * By Finwe, December 2001
 */
 
#include "/d/Shire/sys/defs.h"
#include "local.h"

inherit ROAD_BASE;
 
void
create_road_room()
{
    in_exit = BAR_DIR+"bar09_out";
    out_exit = VAL_DIR+"val12";
    set_areadesc("valley");
    set_area("below the");
    set_areaname("the Barrow Downs");
    set_land("Eriador");

    set_extraline("This is a valley at the feet of the Barrow " +
        "Downs. Thick fogs obscure swirl around here, obscuring " +
        "your vision.");
    add_item(({"hole", "entrance"}),
        "The hole, or entrance, leads into the barrow. It looks " +
        "like it was once an ancient entrance but now is nothing " +
        "more than a hole in the side of the hill.\n");
    add_item(({"dirt"}),
        "The dirt is piled up around the hole in the face of the " +
        "barrow. It is dark colored and looks like it's packed " +
        "down from many feet that have walked this way.\n");
    set_add_valley_descrs();


    add_exit(VAL_DIR + "val11", "west");
    add_exit(VAL_DIR + "val13", "southeast");

}
