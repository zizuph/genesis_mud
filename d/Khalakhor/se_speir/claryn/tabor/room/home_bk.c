/*
 * home_bk.c
 *
 * Bee keeper's home near Tabor Sogh.
 *
 * Zima - May 16, 98
 */
#pragma strict_types
#include "room.h"
 
inherit HOMEBASE;
 
public int * query_local_coords() { return ({5, -1}); }
public void  reset_room()         { check_trunk(); }
 
public void create_khalakhor_room()
{
    create_home();
    set_long("   You are in a small rural home near the village of "+
        "Tabor Sogh. Simply enough constructed, the " +
        "walls are lined with little in the way of " +
        "treasures or decorations. A small fireplace " +
        "stands cold against one wall, nearby that " +
        "a small table. A pegboard for cloaks and " +
        "plaides is mounted near the door, and a " +
        "bed sits near the back of the one room " +
        "dwelling.\n");
 
    add_exit(ROOM + "bk_yard", "north");
}
