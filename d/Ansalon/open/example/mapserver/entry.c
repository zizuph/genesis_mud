#include "local.h"
inherit "/std/room";

public void
create_room()
{
    set_short("start/end");
    set_long("Start/end of the path.\n");
    add_exit(THIS_DIR+"rooms/ex-5-0-p", "south", 0, 1);
}
