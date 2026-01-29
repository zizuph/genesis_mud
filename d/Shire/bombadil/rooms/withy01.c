/*
 * Road in the Barrow Downs
 * By Finwe, December 2001
 */
 
#pragma strict_types
 
#include "../local.h"

inherit WITHY_BASE;
 
void
create_withy_room()
{
    set_areadesc("path");
    set_area("along");
    set_areaname("the Withywindle");
    set_land("Old Forest");

    set_extraline("You stand on the eastern border between the " +
        "the Downs and the Old Forest and just south of a clearing. " +
        "Tall trees to the east and south mark the border of the " +
        "two lands as the Withywindle flows into the forest. Plants " +
        "grow alongside the river, hiding it in places from your view.");

    add_exit(ROOMS_DIR + "withy02", "west");
}

