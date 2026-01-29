inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#define SHDIR(ob)    "/d/Kalad/common/guilds/shadow_walkers/ob"

/* The Shadows Walkers of Kabal Guild Hall , Sarr */

void
create_room()
{
    set_short("In a dark tunnel");
    set_long("You now stand in a dark tunnel somewhere in the "+
    "sewers of Kabal. Darkness and evil surrounds you and "+
    "caresses you strangely. The tunnel leads both north "+
    "and south.\n");
    add_item("walls","The walls are carved from stone, and they "+
    "radiate an aura of darkness.\n");
    INSIDE;
    add_prop(ROOM_I_LIGHT,0);
    add_exit(SHDIR(t3),"north",0,-1,1);
    add_exit(SHDIR(t1),"south",0,-1,1);
}

