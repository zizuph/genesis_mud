/*
 * Road in western vales of Anduin.
 * By Finwe, June 2001
 */
 
#pragma strict_types
 
#include "local.h"

inherit VALE_BASE;
void create_vale_room()
{
    set_area("on the west side of");
    set_areaname("the Old Ford");
    set_land("the Vales of the Anduin");
   add_my_desc("To the east is the Old Ford of Anduin. It is " +
        "an ancient ford marking the center of the Vales of " +
        "Anduin. In ancient times, the ford was maintained, " +
        "but now it looks as if it has fallen into disrepair. " +
        "The land is marshy as the river often floods the area " +
        "nearby.\n");

    add_item(({"ford", "old ford"}),
        "The ford is a wide, shallow area in the Anduin that " +
        "allows travellers to cross it. It's rather difficult " +
        "as the river is swift and has been known to wash " +
        "unfortunate victims down river.\n");
    
    set_add_river_close();
    set_add_misty_near();

    reset_shire_room();

    add_exit(WEST_DIR + "wbs1", "south");
    add_exit(WEST_DIR + "rd01", "west");
    add_exit(EAST_DIR + "eford", "east");
}

void reset_shire_room()
{
}


