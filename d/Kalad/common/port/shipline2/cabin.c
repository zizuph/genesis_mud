#include "../default.h"
inherit "/std/room";

void
create_room()
{
    add_prop(ROOM_I_INSIDE,1);
    set_short("Captain's Cabin");
    set_long("You stand within the captain's chambers.\n"+
      "This room is rather spartan in its decor. The wooden plank walls are "+
      "as bare as the day the ship first set sail, or so it seems. An old "+
      "steering wheel hangs on the back wall, and a small desk sits in one "+
      "corner. Two small portholes look out into the sea.\n");
    add_item(({"decor"}),"There is little of value or beauty in this "+
      "room, just the necessities.\n");
    add_item(({"wooden plank walls","wooden walls","plank walls","wooden wall","plank wall","wall","walls","wall"}),
      "Made of aged timber, it serves as a waterproof barrier for the "+
      "captain.\n");
    add_item(({"old steering wheel","old wheel","steering wheel"}),"An "+
      "ancient-looking steering device for some ship.\n");
    add_item(({"small desk","desk"}),"Exactly what it looks like, a plain "+
      "wooden desk. Its top is bare and squeaky clean.\n");
    add_item(({"small portholes","small porthole","portholes","porthole"}),
      "Gazing out, the endless rise and fall of the sea fills your vision.\n");
    add_exit(PORT + "shipline2/upperdeck", "out");
}

