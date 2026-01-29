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
    set_vbfc_extra(forest_desc2);
    reset_shire_room();
    add_forest_herbs();

    add_exit(FOREST_DIR + "forest07", "north",0,4, check_player(2));
    add_exit(FOREST_DIR + "forest25", "south",0,4, check_player(2));
    add_exit(FOREST_DIR + "forest18", "east",0,4, check_player(0));
    add_exit(FOREST_DIR + "forest11", "northwest",0,4, check_player(0));
}

void reset_shire_room()
{
    set_searched(0);

}
