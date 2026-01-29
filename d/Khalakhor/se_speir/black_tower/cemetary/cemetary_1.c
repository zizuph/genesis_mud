/*
 * cemetary_1
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
    add_exit(CEMETARY + "cemetary_4", "north");
    add_exit(GROUNDS + "grounds_16", "east");
    add_exit(CEMETARY + "cemetary_2", "west");
    add_exit(CEMETARY + "cemetary_5", "northwest");
}