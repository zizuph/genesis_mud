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
    add_forest_herbs();

    add_exit(FOREST_DIR + "forest07", "north",0,4, check_person);
    add_exit(FOREST_DIR + "forest21", "south",0,4, check_person);
    add_exit(FOREST_DIR + "forest12", "west",0,4, check_person);
    add_exit(FOREST_DIR + "forest20", "southwest", 0,4, check_person);
 
}

void reset_shire_room()
{
    set_searched(0);

}
