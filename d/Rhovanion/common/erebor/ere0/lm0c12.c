inherit "/d/Rhovanion/lib/room";

#include "/sys/macros.h"
#include "/d/Rhovanion/defs.h"
#define CAVE_DIR ERE_DIR + "ere0/"

create_room()
{

    set_short("On the Road to Dale.\n");
    set_long(
    " " +
    " " +
    " " + 
    " " +
    " " +
    " " +
    "\n");

    add_item(({"river", "running"}),
    "The River Running flows by steadily just to the west of you " +
    "and continues towards the long lake in the south.\n");
      
    add_exit(CAVE_DIR+ "lm0c11","northeast");
    add_exit(CAVE_DIR+ "lm0c13","west");

}

