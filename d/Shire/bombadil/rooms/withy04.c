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

    set_extraline("The path runs west deeper into the Old Forest. " +
        "The trees seem more ominous and threatening, and they " +
        "even seem to be moving around even though no wind or " +
        "breeze is evident. ");

    add_exit(ROOMS_DIR + "withy03", "northeast"); 
    add_exit(ROOMS_DIR + "withy05", "west");
}

