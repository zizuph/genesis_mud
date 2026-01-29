#include "defs.h"
inherit SECRET_ROOM;
/* SARR */

void
create_room()
{
    ::create_room();
    set_short("Inside a secret passage");
    set_long("You are now in a small, dim tunnel. It is damp here, "+
    "as well as cold. Ahead to the east, however, you see some light.\n");
    add_exit(MTRAIL_DIR + "secret1","west",0);
    add_exit(MTRAIL_DIR + "secret3","east",0);
}
