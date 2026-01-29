/*
 * storage
 *
 * In this room players can find the tattered remains
 * of white riding cloaks that can be stained black
 * for use in the first demon quest.
 *
 * Khail - July 8/97
 */
#pragma strict_types

#include "tower.h"

inherit TOWERBASE;

public void
create_khalakhor_room()
{
    set_short("within the ruins of an ancient tower");
    set_long("You are inside a wide, circular room in " +
        "the ruins of an ancient tower. The stone walls, " +
        "once strong, now seem on the verge of collapse. " +
        "Two archways are visible, leading into other " +
        "parts of the tower, and the rest of the walls " +
        "are dominated by the rotting remains of " +
        "shelves, racks and pegs. You notice a steel " +
        "trunk lying in one corner, as well.\n");

    add_exit(TOWER + "entrance", "southwest");
    add_exit(TOWER + "shrine", "west");
}