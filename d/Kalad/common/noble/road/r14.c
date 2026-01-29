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
    add_item("banner","It is red-black and reads: House of Cepheque.\n");
    add_item("gate","The gate leads into the garden area.\n");
    add_item("garden","A very fine and beautifuly crafted garden.\n");
    add_item("estate","A large mansion surrounded by beautiful "+
    "gardens.\n");
    add_item("mansion","It is large and finely crafted, and many "+
    "red-black banners hang around it.\n");
    add_item("road","A very nice white-stoned road that is clean "+
    "and well-kept.\n");
    add_prop(ROOM_NO_TIME_DESC,1);
    add_exit(NOBLE(wayfarer/s4),"north",0,0,-1);
    add_exit(NOBLE(cepheque/g1),"west","@@block@@",0,0);
}

int
block()
{
    write("A guard stops you and says that the Lord is not yet "+
    "receiving visitors.\n");
    return 1;
}
