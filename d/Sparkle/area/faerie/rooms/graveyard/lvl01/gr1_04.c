/*
 * The graveyard of Faerie
 * This room leads down when the tombstone is pushed.
 * The routines are in base_common.c
 * By Finwe, August 2004
 */

#include "defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <language.h>

inherit "/std/room";
inherit GRAVEYARD_BASE;

int headstone_moved = 0;    // 0 = not pushed, 1 = pushed

void
create_graveyard_room()
{
    set_long(grave_above3);
    add_my_desc("@@headstone_descr@@\n");

    set_aboveground();
    add_exit(GRAVE1_DIR + "gr1_08",  "south");
    add_exit(GRAVE1_DIR + "gr1_05",  "east");
    
    down_exit = GRAVE2_DIR + "gr2_04";  // downstairs room it connects to
    reset_room();
}


void
reset_room()
{
    remove_exit("down");
    headstone_moved = 0;
}


init()
{
    ::init();
    add_action("move_headstone","move");
    add_action("move_headstone","push");
}
