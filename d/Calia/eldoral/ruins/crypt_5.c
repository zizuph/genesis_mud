#pragma strict_types

#include "defs.h"

inherit CRYPTBASE;

public void
create_room()
{
    create_crypt();

    add_exit(RUIN + "crypt_7", "north");
    add_exit(RUIN + "crypt_8", "east");
    add_exit(RUIN + "crypt_9", "south");
    add_exit(RUIN + "crypt_2", "west");

}
