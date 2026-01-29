inherit "/d/Rhovanion/lib/room";

#include "/sys/macros.h"
#include "/d/Rhovanion/defs.h"
#define CAVE_DIR ERE_DIR + "ere0/"

create_room()
{

    set_short("On a small stone bridge.\n");
    set_long(
    " " +
    " " +
    " " + 
    " " +
    " " +
    " " +
    "\n");

    add_item(({"river", "running"}),
    "The River Running flows under the bridge from the west and continues " +
    "east where it twists towards the south and the Long Lake.\n");
      
    add_item(({"bridge"}),
    "It is a small stone bridge spanning over the River Running, " +
    "the stones on which you are standing seem to be well used.\n");
    
    add_exit(CAVE_DIR+ "lm0c1","north");
    add_exit(CAVE_DIR+ "lm0c5","south");
    add_exit(CAVE_DIR+ "lm0c61","southwest");

}

