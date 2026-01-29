/* File: /d/Shire/common/trollsh/trollsh14.c */
#include "defs.h"
inherit "/d/Shire/common/trollsh/shawrom"; /*master object*/

create_shawrom()
{

    set_short("Deep in the Trollshaws on a ridge");
    set_extraline("You are south of a large depression in the " +
        "Trollshaws. It's almost like a small valley with a " +
        "narrow path leading through it. Another path leads up " +
        "to another bushy ridge to the north. To the east the " +
        "ridge continues.\n");

    add_item(({"depression"}),
	    "The depression bends down between the two ridges. It is " +
        "full of bushes making it almost impossible to go that " +
        "way, except for the path going through it.\n");


    add_exit(TROLLSH_DIR +  "shaws12", "west", 0, 1);
    add_exit(TROLLSH_DIR + "shaws15", "north", 0, 1);
    add_exit(TROLLSH_DIR +  "shaws17", "east", 0, 1);
}
