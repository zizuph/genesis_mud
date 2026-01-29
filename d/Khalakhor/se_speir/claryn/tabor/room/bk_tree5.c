/*
 * bk_tree5.c
 *
 * Up in one of the trees of the keeper's grove
 *
 * Zima - May 16, 98
 */
#pragma strict_types
#include "/d/Khalakhor/sys/defs.h"
#include <stdproperties.h>
#include "room.h"
inherit  BK_TREEBASE;
 
public void
create_khalakhor_room()
{
    create_tree_rm();
 
    add_exit(ROOM + "bk_grove5", "down", "@@do_climb", 0, 1);
    set_grove_rm(ROOM+"bk_grove5");
    set_bee_home(ROOM+"bk_tree5");
}
