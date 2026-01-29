/*
 * cemetary_8
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
    add_exit(CEMETARY + "cemetary_7", "east");
    add_exit(CEMETARY + "cemetary_4", "southeast");
    add_exit(CEMETARY + "cemetary_5", "south");
    add_exit(CEMETARY + "cemetary_6", "southwest");
    add_exit(CEMETARY + "cemetary_9", "west");
}