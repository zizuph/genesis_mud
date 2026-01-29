/*
 * cemetary_2
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
    add_exit(CEMETARY + "cemetary_5", "north");
    add_exit(CEMETARY + "cemetary_4", "northeast");
    add_exit(CEMETARY + "cemetary_1", "east");
    add_exit(CEMETARY + "cemetary_3", "west");
    add_exit(CEMETARY + "cemetary_6", "northwest");
}