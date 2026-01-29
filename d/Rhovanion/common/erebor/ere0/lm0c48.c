inherit "/d/Rhovanion/lib/room";

#include "/sys/macros.h"
#include "/d/Rhovanion/defs.h"
#define CAVE_DIR ERE_DIR + "ere0/"

create_room()
{

    set_short("On a mountain road.\n");
    set_long(
    " " +
    " " +
    " " + 
    " " +
    " " +
    " " +
    "\n");

    add_item(({"river", "running"}),
    "The River Running appears from underneath the bridge to the northwest of " +
    "you and continues towards the Long Lake in the south.\n");
   
    add_exit(CAVE_DIR+ "lm0c49","southwest");
    add_exit(CAVE_DIR+ "lm0c47","northeast");
    add_exit(CAVE_DIR+ "lm0c46","north");
}
