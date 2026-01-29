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

    add_item(({"river", "running"}),
    "The River Running flows directly to the east of you then turns " +
    "west here where you're standing, the twists south again towards " +
    "the long lake.\n");
      
    
    add_exit(CAVE_DIR+ "lm0c8","northeast");

}

