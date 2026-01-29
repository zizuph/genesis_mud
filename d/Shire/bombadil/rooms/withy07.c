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

    set_extraline("The forest grows thick here, almost forbidding " +
        "you to go further into the forest. The river continues " +
        "flowing south and west into the woods.");

    add_exit(ROOMS_DIR + "withy06", "northeast"); 

}

