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
    set_vbfc_extra(forest_desc5);
    reset_shire_room();
    add_forest_herbs();

    set_add_white_stone("bottom edge", "right edge");

    add_exit(FOREST_DIR + "forest31", "north",0,4, check_person);
    add_exit(FOREST_DIR + "track01", "south",0,4, check_person);
    add_exit(FOREST_DIR + "forest37", "west",0,4, check_person);
    add_exit(FOREST_DIR + "forest45", "southeast",0,4, check_person);
    add_exit(FOREST_DIR + "forest32", "northeast",0,4, check_person);
    add_exit(FOREST_DIR + "forest44", "southwest",0,4, check_person);

}

void reset_shire_room()
{
    set_searched(0);

}
