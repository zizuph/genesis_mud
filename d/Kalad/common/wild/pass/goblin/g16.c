inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* Sarr */

void
create_room()
{
    ::create_room();
    INSIDE;
    add_prop(ROOM_I_LIGHT,0);
    set_short("Dim Tunnel");
    set_long("You are in a dark, dusty tunnel. It is not as murky or "+
    "smelly here compared to the other rooms. The tunnel continues to "+
    "the west.\n");
    add_exit("/d/Kalad/common/wild/pass/goblin/g17","west",0,1,1);
    add_exit("/d/Kalad/common/wild/pass/goblin/g15","east",0,1,1);
}

