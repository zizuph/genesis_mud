inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#define SHDIR(ob)    "/d/Kalad/common/guilds/shadow_walkers/ob"

/* The Shadows Walkers of Kabal Guild Hall , Sarr */

void
create_room()
{
    set_short("In a dark tunnel");
    set_long("You stand now at an intersection of this dark "+
    "sewere tunnel. To the west and east, you see the tunnel "+
    "dissapear into blackness, while south is the way out of "+
    "this dark place. The walls are cold and dark, and shadows "+
    "gather everywhere.\n");
    add_item("walls","The walls are carved from stone, and they "+
    "radiate an aura of darkness.\n");
    INSIDE;
    add_prop(ROOM_I_LIGHT,0);
    add_exit(SHDIR(t4),"west",0,-1,1);
    add_exit(SHDIR(t5),"east",0,-1,1);
    add_exit(SHDIR(t2),"south",0,-1,1);
}

