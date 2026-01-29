#include "local.h"

inherit SHIRE_ROOM;

void
create_shire_room()
{
    set_short("Bank of Anduin");
    set_long("To the east lies Anduin, the great river, and beyond " +
      "it, Mirkwood.  The river is shallow enough to be forded at " +
      "this spot, though it looks impassable to the north and the south.  " +
      "Back west lie the Misty Mountains, and the plains follow the " +
      "river north and south.\n");

    add_exit(MISTY_DIR + "oldpath1", "west");
    add_exit(MISTY_DIR + "oldpath3", "east");
}
