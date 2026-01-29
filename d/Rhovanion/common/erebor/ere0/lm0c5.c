inherit "/d/Rhovanion/lib/room";

#include "/sys/macros.h"
#include "/d/Rhovanion/defs.h"
#define CAVE_DIR ERE_DIR + "ere0/"

create_room()
{

    set_short("On a road south of a small bridge.\n");
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
    
    add_exit(CAVE_DIR+ "lm0c4","north");
    add_exit(CAVE_DIR+ "lm0c6","south");
    add_exit(CAVE_DIR+ "lm0c7","southwest");

}

