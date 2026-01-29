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
    set_vbfc_extra(forest_desc3);
    reset_shire_room();

    add_exit(FOREST_DIR + "track07", "north",0,4, check_player(2));
    add_exit(FOREST_DIR + "forest34", "south",0,4, check_player(0));
    add_exit(FOREST_DIR + "forest26", "east",0,4, check_player(0));
    add_exit(FOREST_DIR + "forest18", "northeast",0,4, check_player(0));

}

void reset_shire_room()
{
}
