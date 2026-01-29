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
    set_short("Beyond the breakwaters of Kalaman");
    set_long("The ship is just beyond the breakwaters of Kalaman, " +
      "which you can see do the south. The waters of the " +
      "Vingaard River seem quite calm.\n");
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);

    reset_flotsam_room();
}
