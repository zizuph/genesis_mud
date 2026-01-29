// File: /d/Shire/common/trollsh/trollsh20.c */
inherit "/d/Shire/common/trollsh/shawrom_new"; /*master object*/
#include "defs.h"

create_shawrom()
{

    set_short("Deep in the Trollshaw");
    set_extraline("Here the shaws grow terribly dense. " +
    "Several spruces and sturdy bushes makes this place very " +
    "narrow.");

    add_item(({"path"}),"There are two paths here.\n");

    add_exit(TROLLSH_DIR + "shaws21", "west", 0);
    add_exit(TROLLSH_DIR + "shaws19", "south", 0);
    add_exit(TROLLSH_DIR + "shaws16", "southwest", 0);
   
}
