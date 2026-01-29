inherit "/d/Gondor/common/room";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"

void
create_room()
{
    set_short("in the upstairs hallway of the inn");
    set_long(BSN("You are in the long hall to the rooms of the "+
       "Dragon's Claw Inn. The hall continues west towards more doors and "+
       "east lie the stairs down to the common room. There are two doors "+
       "here, one to the north and one to the south."));
    add_prop(ROOM_I_INSIDE,1);
    add_item(({"red carpet","carpet"}),BSN("The stains on the "+
       "carpet look to be mostly ale, though you guess that there is "+
       "vomit here and there also. Other than that it looks nice."));
    add_exit(PELAR_DIR + "homes/inn/innrm1","south",0);
    add_exit(PELAR_DIR + "homes/inn/innrm3","north",0);
    add_exit(PELAR_DIR + "homes/inn/innhall1","east",0);
    add_exit(PELAR_DIR + "homes/inn/innhall3","west",0);
}
