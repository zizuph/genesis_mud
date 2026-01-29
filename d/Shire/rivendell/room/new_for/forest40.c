/*
 * Forest near Rivendell
 * By Finwe, August 1998
 */
 
#pragma strict_types
 
#include "local.h"
 
inherit FOREST_BASE;
 
void
create_forest_room()
{
    set_vbfc_extra(forest_desc5);
    reset_shire_room();

    add_exit(FOREST_DIR + "forest34", "north",0,4, check_player(0));
    add_exit(FOREST_DIR + "forest48", "south",0,4, check_player(2));
    add_exit(FOREST_DIR + "forest41", "east",0,4, check_player(0));
    add_exit(FOREST_DIR + "forest49", "southeast",0,4, check_player(0));
}

void reset_shire_room()
{
}
