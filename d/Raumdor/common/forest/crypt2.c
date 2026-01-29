#include "defs.h"
inherit CRYPT_ROOM;

/* SARR */

object door;

void
create_room()
{
    ::create_room();
    set_long("You are now on the other side of the great door. You "+
    "see nothing much in this room. It is just a long tunnel leading "+
    "into darkness to the south.\n");
    door = clone_object(FOREST_DIR + "c_door2");
    door->move(TO);
    add_exit(FOREST_DIR + "crypt3","south");
}
