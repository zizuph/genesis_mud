/*
 * bk_grove4.c
 *
 * One of the rooms in the bee keeper's grove of trees
 *
 * Zima - May 16, 98
 */
#pragma strict_types
#include "/d/Khalakhor/sys/defs.h"
#include <stdproperties.h>
#include "room.h"
inherit  BK_GROVEBASE;
 
public void
create_khalakhor_room()
{
    create_grove();
 
    add_exit(ROOM + "bk_grove5","northwest");
    add_exit(ROOM + "bk_tree4", "up", "@@do_climb", 0, 1);
    set_tree_rm(ROOM+"bk_tree4");
}
