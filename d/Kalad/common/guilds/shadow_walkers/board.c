inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#define SHDIR(ob)    "/d/Kalad/common/guilds/shadow_walkers/ob"

/* The Shadows Walkers of Kabal Guild Hall , Sarr */

void
create_room()
{
    set_short("In a shadowy room");
    set_long("You feel something magical about this room. There "+
    "is nothing in the room, except for a board in the center. "+
    "The walls are plain and bare. You feel that the board "+
    "you look at is shared by everyone in the world.\n");
    INSIDE;
    add_prop(ROOM_I_LIGHT,1);
    add_exit(SHDIR(t11),"southwest",0,-1,1);
    clone_object("/d/Genesis/obj/board")->move(TO);
}
