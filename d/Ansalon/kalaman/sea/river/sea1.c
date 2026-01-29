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
    set_short("Estuary of the Vingaard River");
    set_long("Surrounding you is the estuary of the Vingaard River, " +
      "where the river heads to the northeast to meet up with the " +
      "Courrain Ocean, and to the west heads down into the plains " +
      "of Solamnia. To your southeast you can see the lights of " +
      "Kalaman.\n");
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);

    reset_flotsam_room();
}
