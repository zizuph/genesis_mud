inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#define SHDIR(ob)    "/d/Kalad/common/guilds/shadow_walkers/ob"

/* The Shadows Walkers of Kabal Guild Hall , Sarr */


void
create_room()
{
    set_short("In a dusty room");
    set_long("You now find yourself in a dusty room. There are "+
    "shelves along the walls, as well as tables. This looks like "+
    "it is some sort of storage room.\n");
    add_item("shelves","They are made of wood.\n");
    add_item("tables","They are made of old wood.\n");
    add_item("walls","The walls are carved from stone, and they "+
    "radiate an aura of darkness.\n");
    INSIDE;
    add_prop(ROOM_I_LIGHT,1);
    add_exit(SHDIR(t11),"west",0,-1,1);
}
