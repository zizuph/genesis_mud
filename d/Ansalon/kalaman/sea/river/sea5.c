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
    set_short("near Vingaard Keep on the Vingaard River");
    set_long("You are sailing along the great Vingaard River, longest river in Ansalon. " +
      "Looking to your west you can see the great plains of Solamnia stretching out " +
      "all the way to the Vingaard Mountains. Slightly to your southwest, you see the rising " +
      "walls of Vingaard Keep, the stronghold of the Knights of Solamnia.\n");
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);

    reset_flotsam_room();
}
