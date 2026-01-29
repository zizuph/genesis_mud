/*
 * Upper corridor in Elrond's house
 * By Finwe, December 1997
 */
 
#pragma strict_types
 
#include "local.h"
 
inherit HOUSE_IN_BASE;

void
create_house_room()
{
    set_short("An upstairs corridor in the house of Elrond");
    set_long("You stand outside some rooms in an upstairs " +
        "corridor in the house of Elrond. The corridor is " +
        "wide and the walls are painted off-white. Some " +
        "paintings decorate the walls, giving the the area " +
        "some color.\n");

    add_item(({"painting", "paintings"}),
        "The paintings depict the founding of Imladris.\n");
    set_extra_wall("Ornate paintings decorate the walls.");

    add_exit(VALLEY_DIR + "u_gr01",  "north");
    add_exit(VALLEY_DIR + "u_cor02", "east");
}
 

