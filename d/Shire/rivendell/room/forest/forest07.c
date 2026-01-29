/*
 * Forest near Rivendell
 * By Finwe, August 1998
 */
 
#pragma strict_types
 
#include "local.h"
 
inherit FOREST_BASE;

int check_players = 1;
 
void
create_forest_room()
{
    set_vbfc_extra(forest_desc1);
    reset_shire_room();
    add_forest_herbs();
    add_forest_herbs();

    add_exit(FOREST_DIR + "forest13", "south",0,4, check_player(2));
    add_exit(FOREST_DIR + "forest08", "east",0,4, check_player(0));

 
}

void reset_shire_room()
{
    set_searched(0);

}
