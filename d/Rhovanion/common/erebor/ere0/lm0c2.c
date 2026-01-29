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
    "The River Running appears from underneath the bridge just to the west of," +
    "you and continues towards the Long Lake in the south.\n");
 
    add_item("bridge",
    "It is a small bridge made out of the hardest granite.\n");
    
    add_exit(CAVE_DIR+ "lm0c1","northwest");
    add_exit(CAVE_DIR+ "lm0c3","southeast");
}

