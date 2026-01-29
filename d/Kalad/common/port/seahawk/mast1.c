#include "../default.h"
inherit PORT_ROOM;

void
create_port_room()
{
    set_short("You are holding on tightly to the mast");
    set_long("You are holding on tightly to the main mast. All around "+
      "the ship are the docks to which it is tied to. Passing seagulls "+
      "look at you as if you were out of your element.\n");
    add_item(({"main mast","mast"}),"A thick, wooden mast that serves "+
      "as the ship's primary supporter of the sails.\n");
    add_item(({"sails","sail"}),"The billowing white sails lie just "+
      "above and below you.\n");
    add_item(({"seagulls","seagull"}),"The white sea birds are peering "+
      "at you curiously.\n");

    add_prop(ROOM_NO_TIME_DESC,1);

    add_exit(PORT + "seahawk/mast2",  "up", 0,2);
    add_exit(PORT + "seahawk/boat3",  "down", 0,2);
}

