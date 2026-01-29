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

    set_extraline("A large window is set into the hill. Flowers and bushes grow in front of it, and alongside the garden is a path. The path winds its way through a lawn. ");

    add_item(({"window", "large window"}),
        "The window is made of panes of glass. Each pane of glass " +
        "is held in the window with narrow strips of lead.\n");

    add_bagend_front();
    add_bagend_garden();
    add_windows();

    reset_shire_room();

    add_exit(BE_ROOMS + "path14", "east");
    add_exit(BE_ROOMS + "back_porch", "west");
    add_exit(BE_ROOMS + "lawn03", "south");
}

void reset_shire_room()
{
    ::reset_shire_room();
    set_searched(0);
    lawn_status(0);
}
