inherit "/d/Gondor/common/room";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"

void
create_room()
{
    set_short("in the upstairs hallway of the inn");
    set_long(BSN("You are in the long hall connecting the upstairs "
      + "rooms of the Dragon's Claw. To the east the hall continues "
      + "to more sets of doors. A doorway leads north into a room."));
    add_prop(ROOM_I_INSIDE,1);
    add_item(({"red carpet","carpet"}),BSN("The stains on the "+
       "carpet look to be mostly ale, though you guess that there is "+
       "vomit here and there also. Other than that it looks nice."));
    add_exit(PELAR_DIR + "homes/inn/innrm2","north",0);
    add_exit(PELAR_DIR + "homes/inn/innhall2","east",0);
}

