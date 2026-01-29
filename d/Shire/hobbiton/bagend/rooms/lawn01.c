/*
 * Outside room in Bag End
 * By Finwe, April 2020
 */

#include "/d/Shire/sys/defs.h"
#include "../defs.h"

inherit BASE_OUTSIDE;

int lawn_cut = 0;

void create_outside_room()
{
    set_areadesc("lawn");
    set_area("outside");
    set_areaname("a large smial");
    set_land("Hobbiton");
    set_areatype(0);

    set_long("@@long_desc");

    set_extraline("The lawn is thick and green. A fence .....");


    room_add_object(BE_OBJ + "lawn01_gate");

    reset_shire_room();

    add_exit(BE_ROOMS + "path17", "north");
    add_exit(BE_ROOMS + "lawn02", "southeast");
}

void reset_shire_room()
{
    ::reset_shire_room();
    set_searched(0);
    lawn_status(0);
}
