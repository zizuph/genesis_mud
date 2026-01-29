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
    set_short("the Vingaard River");
    set_long("You are sailing along the great Vingaard River, longest river in Ansalon. " +
      "Looking to your west you can see the great plains of Solamnia stretching out all the " +
      "way to the Vingaard Mountains. Squinting, you can just make out the ruins of an ancient " +
      "castle, destroyed during the peasant rebellion not too long ago. To your east " +
      "a smaller river joins with the Vingaard, marking the boundary between Nightlund " +
      "and Gaardlund.\n");
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);

    reset_flotsam_room();
}
