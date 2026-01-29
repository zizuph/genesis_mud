/*
 * Road in the Barrow Downs
 * By Finwe, December 2001
 */
 
#include "../local.h"
inherit PICK_LILIES;
inherit WITHY_BASE;
 
void
create_withy_room()
{
    set_areadesc("path");
    set_area("along");
    set_areaname("the Withywindle");
    set_land("Old Forest");

    set_extraline("The river angles southwest past tall trees. " +
        "It flows quietly along plants and flowers growing along " +
        "its edge. Tall trees grow over the river, blocking most " +
        "of the light that falls here.");

    add_exit(ROOMS_DIR + "withy05", "east"); 
    add_exit(ROOMS_DIR + "withy07", "southwest");
}


init()
{
    add_action("pick_lily", "pick");
    ::init();
}

void reset_shire_room()
{
    //add_stuff();
    lily_counter = 0;
}
