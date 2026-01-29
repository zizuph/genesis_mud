/*
 * cemetary_5
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
    add_exit(CEMETARY + "cemetary_8", "north");
    add_exit(CEMETARY + "cemetary_7", "northeast");
    add_exit(CEMETARY + "cemetary_6", "east");
    add_exit(CEMETARY + "cemetary_1", "southeast");
    add_exit(CEMETARY + "cemetary_2", "south");
    add_exit(CEMETARY + "cemetary_3", "southwest");
    add_exit(CEMETARY + "cemetary_6", "west");
    add_exit(CEMETARY + "cemetary_9", "northwest");
}