inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#define SHDIR(ob)    "/d/Kalad/common/guilds/shadow_walkers/ob"

/* The Shadows Walkers of Kabal Guild Hall , Sarr */

void
create_room()
{
    set_short("In a hallway");
    set_long("You are now in a short hallway leading from the "+
    "main room. The stone walls around you are cool to the touch, "+
    "and shadows dance around everywhere. There is a torch on the "+
    "wall providing light. To the north you see what looks like "+
    "a mail room, while to the west you see another resting room.\n");

    add_item("torch","It casts dim light in the room.\n");
    INSIDE;
    add_prop(ROOM_I_LIGHT,1);
    add_exit(SHDIR(t10),"east",0,-1,1);
    add_exit(SHDIR(po),"north",0,-1,1);
    add_exit(SHDIR(med),"west",0,-1,1);
}
