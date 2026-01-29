#include "local.h"

inherit SHIRE_ROOM;

void
create_shire_room()
{
    set_short("East of Anduin");
    set_long("You are on the east bank of the Anduin. To the east, "+
      "a wide plain stretches towards dark Mirkwood visible in the distance.\n");

    add_exit(MISTY_DIR + "togon2", "north");
    add_exit(MISTY_DIR + "togon4", "south");
}
