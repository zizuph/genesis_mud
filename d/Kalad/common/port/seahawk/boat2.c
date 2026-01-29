#include "../default.h"
inherit PORT_ROOM;

void
create_port_room()
{
     /*always do this*/
    add_prop(ROOM_NO_TIME_DESC,1);

    set_short("Side of the Seahawk");
    set_long("This is the side of the ship closest to the mainland "+
      "Port District. The noisy cries of seagulls combines with a slight "+
      "ocean breeze to bring you a feeling of serenity. The floor beneath "+
      "creaks ever so slightly as you move across the deck.\n");
    add_item(({"mainland","port district","district"}),"Peering over the "+
      "side of the ship you can see the many wooden building of the "+
      "port area of Kabal.\n");
    add_item(({"wooden buildings","buildings","building"}),"Little can "+
      "be made out from this distance.\n");
    add_item(({"seagulls","seagull"}),"Graceful white birds that fly "+
      "above you.\n");
    add_item(({"floor","deck"}),"A few tiny rat holes are visible in "+
      "the ship's deck.\n");

    add_exit(PORT + "seahawk/boat1", "west");
    add_exit(PORT + "seahawk/boat6", "southeast");
    add_exit(PORT + "seahawk/boat4", "south");
}

