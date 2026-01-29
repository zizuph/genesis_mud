inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#define SHDIR(ob)    "/d/Kalad/common/guilds/shadow_walkers/ob"

/* The Shadows Walkers of Kabal Guild Hall , Sarr */

void
create_room()
{
    object wire,bomb;
    set_short("In a dark tunnel");
    set_long("You stand now at a dark bend in this tunnel. The "+
    "tunnel bends sharply to the northeast. You can see light "+
    "up ahead somewhere.\n");
    add_item("walls","The walls are carved from stone, and they "+
    "radiate an aura of darkness.\n");
    INSIDE;
    add_prop(ROOM_I_LIGHT,0);
    add_exit(SHDIR(t6),"northeast",0,-1,1);
    add_exit(SHDIR(t3),"east",0,-1,1);
    wire = clone_object(SHDIR(trip_wire));
    bomb = clone_object(SHDIR(fire_bomb));
    bomb->set_fire_str(100);
    wire->set_hooked(bomb);
    wire->set_hidden_level(80);
    wire->move(TO);
}

