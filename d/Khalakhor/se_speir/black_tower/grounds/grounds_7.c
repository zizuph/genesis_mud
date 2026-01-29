/*
 * grounds_7
 *
 * This room is on a path leading around the back
 * of the tower to the black spring.
 *
 * Khail - July 7/97
 */
#pragma strict_types

#include "grounds.h"

inherit STDGROUNDS;

public void
create_khalakhor_room()
{
    create_grounds();
    add_exit(GROUNDS + "grounds_6", "east");
    add_exit(GROUNDS + "grounds_8", "west");
}