inherit "/d/Rhovanion/lib/room";

#include "/sys/macros.h"
#include "/d/Rhovanion/defs.h"
#define CAVE_DIR ERE_DIR + "ere0/"

create_room()
{

    set_short("On a small road following the River Running.\n");
    set_long(
    " " +
    " " +
    " " + 
    " " +
    " " +
    " " +
    "\n");

    
     add_exit(CAVE_DIR+ "lm0c8","east");
    

}

