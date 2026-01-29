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

    set_extraline("The river bubbles along the path, under the " +
        "trees which grow thick here. The light seems a litle " +
        "darker as it filters through the trees. The flowers " +
        "growing along the river bank bloom in vibrant colours.");

    add_exit(ROOMS_DIR + "withy01", "east"); 
    add_exit(ROOMS_DIR + "withy03", "west");
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
