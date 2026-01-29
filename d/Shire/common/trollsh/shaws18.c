/* File: /d/Shire/common/trollsh/trollsh18.c */
inherit "/d/Shire/common/trollsh/shawrom"; /*master object*/
#include "defs.h"



create_shawrom()
{
    set_short("East in the Trollshaw");
    set_extraline("The bushes and pine trees grow thick. There " +
        "is a ridge building up to the south and and a narrow " +
        "path going up to another ridge to the west. To the " +
        "north is another path leading someplace.\n");

    add_exit(TROLLSH_DIR + "shaws15", "west", 0, 2);
    add_exit(TROLLSH_DIR + "shaws17", "south", 0, 2);
    add_exit(TROLLSH_DIR + "shaws19", "north", 0, 2);
}
