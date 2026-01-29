#include "defs.h"
inherit CRYPT_ROOM;

/* SARR */


void
create_room()
{
    ::create_room();
    set_long("You are in a long dark tunnel.\n");
    add_exit(FOREST_DIR + "crypt2","north");
    add_exit(FOREST_DIR + "crypt4","south");
}
