/*
 * cemetary_3
 *
 * This room is in the cemetary beside the black
 * tower.
 *
 * Khail - July 7/97
 */
#pragma strict_types

#include "cemetary.h"

inherit STDCEM;

public void
create_khalakhor_room()
{
    create_cemetary();
    add_exit(CEMETARY + "cemetary_6", "north");
    add_exit(CEMETARY + "cemetary_5", "northeast");
    add_exit(CEMETARY + "cemetary_2", "east");
}