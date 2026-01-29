inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

/* Sarr */

void
create_room()
{
    ::create_room();
    set_short("On End Street");
    set_long("You are travelling along End street in the Noble "+
    "district. The street here is very well taken care of, and "+
    "there is hardly any trash or refuse around. Off to your "+
    "east you can see the grand estates of the various rich "+
    "nobles of Kabal. You are just south of the intersection of "+
    "End and Gateway. The hot Kaladian sun beams down on you, "+
    "making you sweat a little.\n");
    hear_bell = 2;
    add_item("street","It is very wall taken care of.\n");
    add_item("estates","Grand houses and gardens of such "+
    "beauty that you are amazed.\n");
    add_exit(NOBLE(gateway-end),"north",0,0,-1);
    add_exit(NOBLE(end/s5),"south",0,0,-1);
}

