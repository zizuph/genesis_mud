/*
 * grounds_15
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
    set_long(query_long() + "A large archway " +
        "stands in the face of the tower here, " +
        "allowing entrance. Twisted scraps of " +
        "iron at the edges hint that a door once " +
        "stood here, but was claimed by the elements " +
        "long ago.\n");
    add_item(({"archway"}),
        "Once the frame of what must have been massive " +
        "doors, the archway is now little more than " +
        "a regularly-shaped hole in the wall.\n");
    add_item(({"scraps", "hinges"}),
        "Fastened to the edges of the archway, these " +
        "must once have been hinges to the now absent " +
        "doors to the tower.\n");

    add_exit(TOWER + "entrance", "north");
    add_exit(GROUNDS + "grounds_14", "east");
    add_exit(GROUNDS + "grounds_16", "west");
}