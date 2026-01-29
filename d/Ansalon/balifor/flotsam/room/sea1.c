#include "/d/Ansalon/balifor/flotsam/local.h"
#include "/d/Ansalon/common/defs.h"

inherit FLOTSAM_OUT;

void
reset_flotsam_room()
{
    return;
}

create_flotsam_room()
{
    set_short("Near Flotsam in Blood Bay");
    set_long("The waves of Blood Bay gently lap against the side " +
      "of the boat. Looking out to sea you notice black clouds, " +
      "clouds that mark the edge of the infamous maelstrom of " +
      "the Bloodsea of Istar. In the opposite direction you " +
      "can see the town of Flotsam, lying upon the shore of " +
      "the Goodlund peninsula like the wreckage of a broken vessel. \n");
    add_item("sea","Yep, there certainly is a lot of it.\n");
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);

    reset_flotsam_room();
}
