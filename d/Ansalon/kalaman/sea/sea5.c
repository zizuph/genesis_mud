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
    set_short("Northern Courrain ocean");
    set_long("Surrounding the ship on both sides are the " +
      "tranquil waters of the Northern Courrain Ocean. " +
      "For a moment, you thought you saw an island to the " +
      "north, but at second glance it was nowhere to be " +
      "seen. Must be your imagination.\n");
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);

    reset_flotsam_room();
}
