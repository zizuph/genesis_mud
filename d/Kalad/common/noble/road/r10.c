inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* Sarr */

void
create_room()
{
    ::create_room();
    set_short("On a small road");
    set_long("You are now on a small, white-stoned paved road, which "+
    "ends here at the entrance to a large estate. The gate here is "+
    "open, and a banner hangs over it.\n");
    add_item("banner","It is red-gold and reads: House of Paullus.\n");
    add_item("gate","The gate leads into the garden area.\n");
    add_item("garden","A very fine and beautifuly crafted garden.\n");
    add_item("estate","A large mansion surrounded by beautiful "+
    "gardens.\n");
    add_item("mansion","It is large and finely crafted, and many "+
    "red-gold banners hang around it.\n");
    add_item("road","A very nice white-stoned road that is clean "+
    "and well-kept.\n");
    add_prop(ROOM_NO_TIME_DESC,1);
    add_exit(NOBLE(road/r8),"east",0,0,-1);
    add_exit(NOBLE(paullus/g1),"north",0,0,-1);
}

