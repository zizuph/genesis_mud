inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#define SHDIR(ob)    "/d/Kalad/common/guilds/shadow_walkers/ob"

/* The Shadows Walkers of Kabal Guild Hall , Sarr */

object ob;
void reset_room();

void
create_room()
{
    set_short("In a dark tunnel");
    set_long("The tunnel twists north again here. The tunnel is "+
    "not lighted here, and darkness surrounds you. You can see "+
    "some light around the bend to the north, however. The air "+
    "of evil is strong, and you feel you are going somewhere "+
    "where you shouldn't.\n");
    add_item("walls","The walls are carved from stone, and they "+
    "radiate an aura of darkness.\n");
    INSIDE;
    add_prop(ROOM_I_LIGHT,0);
    add_exit(SHDIR(t7),"west",0,-1,1);
    add_exit(SHDIR(t9),"north",0,-1,1);
    reset_room();
}

void
reset_room()
{
    if(!ob)
    {
        ob = clone_object(SHDIR(arsonist));
        ob->arm_me();
        ob->move_living("xxx",TO);
    }
}

