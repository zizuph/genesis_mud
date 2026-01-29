/*
 * entrance
 *
 * Nothing special here, it's the entrance to the
 * black tower.
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
    set_long("You stand just within the entrance of " +
        "the ruins of an ancient tower. This hall " +
        "may once have been impressive, but now is " +
        "little more than a circular wall of stone " +
        "adorned by nothing but two flights of " +
        "narrow stone stairs leading up and down. " +
        "Archways cut into the walls lead away into " +
        "other parts of the ruins from here as well.\n");

    add_exit(TOWER + "storage", "northeast");
    add_exit(GROUNDS + "grounds_15", "south");
    add_exit(TOWER + "shrine", "northwest");
    add_exit(TOWER + "stairs_1", "up");
    add_exit(TOWER + "dungeon_1", "down");
}