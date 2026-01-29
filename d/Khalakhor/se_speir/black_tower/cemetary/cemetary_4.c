/*
 * cemetary_4
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
    add_exit(CEMETARY + "cemetary_7", "north");
    add_exit(CEMETARY + "cemetary_1", "south");
    add_exit(CEMETARY + "cemetary_2", "southwest");
    add_exit(CEMETARY + "cemetary_5", "west");
    add_exit(CEMETARY + "cemetary_8", "northwest");
}