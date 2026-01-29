/*
 * The graveyard of Faerie
 * By Finwe, August 2004
 */
 
#include "defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

inherit "/std/room"; 
inherit GRAVEYARD_BASE;
 
void
create_graveyard_room()
{
    set_short("The lowest level of the crypt");
    set_long("You stand beneath the crypt. A very dark presence fills " +
        "the air. Dried blood streaks the walls and the ground. A dark " +
        "altar stands in the center of the room.\n");

    set_underground();

    add_item(({"walls"}),
        "The walls are circular and constructed of gray stones. There " +
        "are streaks of dried blood from unfortunate victims who died " +
        "here. The walls are bare of any decoration.\n");
    add_item(({"ground", "floor"}),
        "The ground is made of gray stones. They are smooth and don't " +
        "have any cracks in them. Dried puddles of blood are scattered " +
        "around the floor and under the altar.\n");
    add_item(({"ceiling"}),
        "The ceiling is round, like the rest of the room. It is flat " +
        "and unadorned. Surprisingly, there isn't any blood on the ceiling.\n");
    add_item(({"blood", "dried blood"}),
        "It has been splattered on the walls and ground. It's a dark " +
        "red color and probably came from victims who died on the altar. " +
        "It also covers the altar and is in dried pools on the ground.\n");
    add_item(({"altar"}),
        "This is a rectangular slab of rock that sits in the middle of " +
        "the room. It is covered with dried blood, from victims who " +
        "died on it by the hand of some unknown creature.\n");

    add_exit(GRAVE3_DIR + "gr3_02", "north");
    add_exit(GRAVE3_DIR + "gr3_07", "southwest");

    reset_room();
}

void
reset_room()
{
    add_npcs(2);
}