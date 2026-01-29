inherit "/d/Gondor/common/room";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"

void
create_room()
{
    set_short("in the upstairs hallway of the inn");
    set_long(BSN("You are at the top of the stairs in the Dragon's "
      + "Claw Inn. The hall continues to the west following a brown "
      + "stained, red carpet. Farther down the hall you can see doors "
      + "on either side."));
    add_prop(ROOM_I_INSIDE,1);
    add_item("doors", BSN("the doors are farther down the hall, you "
      + "would have to get closer to look at them properly."));
    add_item(({"red carpet","carpet"}),BSN("The stains on the "+
       "carpet look to be mostly ale, though you guess that there is "+
       "vomit here and there also. Other than that it looks nice."));
    add_exit(PELAR_DIR + "homes/inn/innhall2","west",0);
    add_exit(PELAR_DIR + "homes/inn/innter","down",0);
}

