#include "local.h"

inherit SHIRE_ROOM;

void
create_shire_room()
{
    set_short("Fording the Anduin");
    set_long("The Anduin runs slowly by here.  At this spot, the river is " +
      "wide and shallow.  The water is warm around your legs.  " +
      "To the east lies more of the old path, and back west lie " +
      "the Misty Mountains.  To the north and south, the river becomes " +
      "swift and deep.\n");

    add_exit(MISTY_DIR + "oldpath2", "west", 0, 5);
    add_exit(MISTY_DIR + "oldpath4", "east", 0, 5);

    add_prop(OBJ_I_CONTAIN_WATER, 1);
}
