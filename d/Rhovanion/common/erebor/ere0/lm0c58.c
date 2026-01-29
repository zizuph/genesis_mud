inherit "/d/Rhovanion/lib/room";

#include "/sys/macros.h"
#include "/d/Rhovanion/defs.h"
#define CAVE_DIR ERE_DIR + "ere0/"

create_room()
{

    set_short("On a path southwest of Lovely Mountain.\n");
    set_long(
    " " +
    " " +
    " " + 
    " " +
    " " +
    " " +
    "\n");

    add_exit(CAVE_DIR+ "lm0c56","southwest"); 
    add_exit(CAVE_DIR+ "lm0c59","northeast");

}

