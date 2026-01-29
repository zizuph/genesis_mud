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
    set_long("You now find yourself at a bend in the tunnel. The "+
    "smell of evil is stronger here...and you can almost feel the "+
    "darkness and corruption in your bones. There is a torch on "+
    "one wall, and it casts fait light in the room.\n");
    add_item("torch","It burns dimly, casting light, but not enought "+
    "to get rid of all the shadows.\n");
    add_item("walls","The walls are carved from stone, and they "+
    "radiate an aura of darkness.\n");
    INSIDE;
    add_prop(ROOM_I_LIGHT,1);
    add_exit(SHDIR(t8),"east",0,-1,1);
    add_exit(SHDIR(t6),"south",0,-1,1);
    reset_room();
}

void
reset_room()
{
    if(!ob)
    {
        ob = clone_object(SHDIR(shadow_menace));
        ob->arm_me();
        ob->move_living("xxx",TO);
    }
}

