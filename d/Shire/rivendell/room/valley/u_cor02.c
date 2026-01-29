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
    set_long("Standing north of the bell tower, you notice the " +
        "corridor turns to the south and west here. The corridor " +
        "is rather plain but still beautiful. North is a guest room " +
        "while east leads to a lovely bedroom, obviously belonging " +
        "to a person of honor. South is the bell tower.\n");

    add_exit(VALLEY_DIR + "u_gr02",  "north");
    add_exit(VALLEY_DIR + "u_cor05",  "south");
    add_exit(VALLEY_DIR + "arwen_rm", "east");
    add_exit(VALLEY_DIR + "u_cor01",  "west");
}
 
