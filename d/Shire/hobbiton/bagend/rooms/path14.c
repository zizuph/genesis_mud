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

    set_extraline("Flagstones mark a path in the grass. In front of the smial grows a garden, It is full of flowers and bushes. ");

    add_item(({"window", "large window"}),
        "The window is made of panes of glass. Each glass pane of glass " +
        "is held in the window with narrow strips of lead.\n");

    add_bagend_front();
    add_bagend_garden();
    add_windows();

    reset_shire_room();

    add_exit(BE_ROOMS + "path13", "east");
    add_exit(BE_ROOMS + "path15", "west");
    add_exit(BE_ROOMS + "lawn04", "south");
}

void reset_shire_room()
{
    ::reset_shire_room();
    set_searched(0);
    lawn_status(0);
}
