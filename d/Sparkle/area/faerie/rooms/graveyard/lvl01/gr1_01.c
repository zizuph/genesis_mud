/*
 * The graveyard of Faerie
 * By Finwe, August 2004
 */
 
#include "defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <language.h>

inherit "/std/room"; 
inherit GRAVEYARD_BASE;
 
void
create_graveyard_room()
{
    set_long(grave_above3);
    add_my_desc("A lone tree grows in the middle of the graveyard. " +
    "It looks ancient and dead.\n");

    add_item(({"Lone tree"}),
        "The lone tree is twisted and gnarled. It looks like it may " +
        "have been a noble tree, but now it is quite dead.\n");
    add_item(({"branches"}),
        "The branches of the dead tree are twisted and point upwards.\n");
    add_item(({"trunk"}),
        "The trunk of the lone tree is twisted and gray colored.\n");

    set_aboveground();
    headstone_moved = 2; // no headstone here

    add_exit(GRAVE1_DIR + "gr1_02",  "east");
    add_exit(GRAVE1_DIR + "gr1_03",  "southwest");

    reset_room();
}

void
reset_room()
{
    add_npcs(0);
}
