inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* Sarr */

void
create_room()
{
    ::create_room();
    set_short("On a small road");
    set_long("You are now on a small, white-stoned paved road. The "+
    "road continues north, but a side gate opens here to the east "+
    "which leads to the garden of a beautiful estate. There is "+
    "a banner over the gate.\n");
    add_item("banner","It is silver-black and reads: House of Drugeworth.\n");
    add_item("gate","The gate leads into the garden area.\n");
    add_item("garden","A very fine and beautifuly crafted garden.\n");
    add_item("estate","A large mansion surrounded by beautiful "+
    "gardens.\n");
    add_item("mansion","It is large and finely crafted, and many "+
    "silver-black banners hang around it.\n");
    add_item("road","A very nice white-stoned road that is clean "+
    "and well-kept.\n");
    add_prop(ROOM_NO_TIME_DESC,1);
    add_exit(NOBLE(road/r3),"south",0,0,-1);
    add_exit(NOBLE(drugeworth/g1),"east","@@block@@",0,0);
    add_exit(NOBLE(road/r6),"north",0,0,-1);
}

int
block()
{
    write("A guard stops you and says that the Lord is not yet "+
    "receiving visitors.\n");
    return 1;
}
