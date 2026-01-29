/*
 * The orchard of Westfarthing
 * By Finwe, February 2020
 */

#include "/d/Shire/sys/defs.h"
#include "../defs.h"

inherit "/d/Shire/ns_road/std/base_orchard.c";

void
create_orchard()
{
    set_areadesc("well tended orchard");
    set_area("in central");
    set_areaname("Southfarthing");
    set_land("the Shire");
    set_areatype(0);

    set_vbfc_extra(road_desc3);

    add_exit(ORCHARD_DIR + "orchard10", "north");
    add_exit(ORCHARD_DIR + "orchard19", "south");
    add_exit(ORCHARD_DIR + "orchard16", "east");

    reset_shire_room();
}

void reset_shire_room()
{
    ::reset_shire_room;
    set_searched(0);
    fruit_counter = 0;
}
