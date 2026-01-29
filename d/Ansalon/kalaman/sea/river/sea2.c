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
      "Looking out to the west you can see the great plains of Solamnia stretching out " +
      "all the way to the Vingaard Mountains, while to the east of the river lies " +
      "Nightlund, a barren plain under control of the forces of darkness, namely " +
      "Lord Soth the Death Knight and his undead minion.\n");
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);

    reset_flotsam_room();
}
