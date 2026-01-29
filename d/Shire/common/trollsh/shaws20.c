// File: /d/Shire/common/trollsh/trollsh20.c */
inherit "/d/Shire/common/trollsh/shawrom"; /*master object*/
#include "defs.h"

create_shawrom()
{

    set_short("Deep in the Trollshaw");
    set_extraline("Here the bushes and trees grow very thick, " +
        "leaving very narrow paths through their growth. " +
        "There are three paths that lead south and west as well " +
        "as southwest through some bushes.\n");

    add_exit(TROLLSH_DIR + "shaws21", "west", 0);
    add_exit(TROLLSH_DIR + "shaws19", "south", 0);
    add_exit(TROLLSH_DIR + "shaws16", "southwest", 0);
   
}
