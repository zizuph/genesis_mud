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
    set_areadesc("path");
    set_area("outside");
    set_areaname("a large smial");
    set_land("Hobbiton");
    set_areatype(0);

    set_long("@@long_desc");

    set_extraline("Flowers grows in front of the smial, hiding a large " +
        "window. Flagstones mark the path in the lawn which is lush and green. ");

    add_item(({"window", "large window"}),
        "It is round and made of many panes of glass. They are held " +
        "together with narrow strips of lead.\n");

    add_bagend_front();
    add_bagend_garden();
    add_windows();

    reset_shire_room();

    add_exit(BE_ROOMS + "porch", "east");
    add_exit(BE_ROOMS + "path13", "west");
    add_exit(BE_ROOMS + "lawn06", "south");
}

void reset_shire_room()
{
    ::reset_shire_room();
    set_searched(0);
    lawn_status(0);
}
