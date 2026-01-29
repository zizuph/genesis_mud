#pragma strict_types

#include "defs.h"

inherit CRYPTBASE;

public void
create_room()
{
    create_crypt();

    add_exit(RUIN + "crypt_4", "north");
    add_exit(RUIN + "crypt_5", "east");
    add_exit(RUIN + "crypt_6", "south");
    add_exit(RUIN + "crypt_1", "west");

}
