inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#define SHDIR(ob)    "/d/Kalad/common/guilds/shadow_walkers/ob"

/* The Shadows Walkers of Kabal Guild Hall , Sarr */

void
create_room()
{
    set_short("In a dark tunnel");
    set_long("You are now at an intersections where two tunnels, "+
    "southeast and southwest, meet into one that heads north. "+
    "There is a torch on the wall here, casting faint light. "+
    "The shadows cling on the walls everywhere, and you see "+
    "movement at the corners at your eyes. On the east wall, you "+
    "see some writing.\n");
    add_item("torch","It burns dimly, casting light, but not enought "+
    "to get rid of all the shadows.\n");
    add_item("east wall","You see strange writing in red.\n");
    add_item("walls","The walls are carved from stone, and they "+
    "radiate an aura of darkness.\n");
    add_cmd_item("writing","read","It reads: Lair of the "+
    "Shadow Walkers -- DRC.\n");
    add_item("writing","It is readable.\n");
    INSIDE;
    add_prop(ROOM_I_LIGHT,1);
    add_exit(SHDIR(t4),"southwest",0,-1,1);
    add_exit(SHDIR(t5),"southeast",0,-1,1);
    add_exit(SHDIR(t7),"north",0,-1,1);
}

