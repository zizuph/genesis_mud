#include "../default.h"
inherit PORT_ROOM;

void
create_port_room()
{
    set_short("The Far End of the Seahawk");
    set_long("This is the far end of the ship. As you move you can feel "+
      "the vessel slowly rock beneath your feet. The noisy call of seagulls "+
      "flying overhead fills the air.\n");
    add_item(({"seagulls"}),"Graceful, white feathered sea birds that "+
      "are flying all over the docks, filling it with their peculiar bird "+
      "calls.\n");

    add_prop(ROOM_NO_TIME_DESC,1);

    add_exit(PORT + "seahawk/boat10", "west");
    add_exit(PORT + "seahawk/boat3", "north");
    add_exit(PORT + "seahawk/boat5", "east");
}

