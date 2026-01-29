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
    set_long("You stand in an upstairs corridor in Elrond's " +
        "house. The corridor is plainly furnished but is still " +
        "nonetheless beautiful. East of here are the central stairs " +
        "and the bell tower while west leads to Elrond's private " +
        "chambers.\n");

    add_exit(VALLEY_DIR + "u_cor05", "east");
    add_exit(VALLEY_DIR + "u_cor03", "west");
}
 
