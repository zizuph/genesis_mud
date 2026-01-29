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
    set_long("Standing south of the bell tower, you notice that " +
		"the corridor ends here. The corridor is plain yet beautiful. " +
		"East of here is a bedroom belonging to a person of great " +
		"honor.\n");

    add_exit(VALLEY_DIR + "u_cor05",    "north");
    add_exit(VALLEY_DIR + "aragorn_rm", "east");
}
 
