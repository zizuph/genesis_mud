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
    set_short("Northern Courrain Ocean");
    set_long("The ship sails through the waters of the " +
      "Northern Courrain Ocean. To your south you see an " +
      "estuary of the Vingaard River opening up, and beyond " +
      "that, the port city of Kalaman.\n");
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);

    reset_flotsam_room();
}
