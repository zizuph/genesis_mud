#include "defs.h"
inherit SECRET_ROOM;
/* SARR */

void
create_room()
{
    ::create_room();
    set_long("You are now in a small tunnel. It leads to the "+
    "east, where you can see some light.\n");
    add_exit(MTRAIL_DIR + "secret4","west",0);
    add_exit(MTRAIL_DIR + "secret6","east",0);
}
