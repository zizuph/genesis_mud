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
    add_forest_herbs();

    add_exit(FOREST_DIR + "forest39", "north",0,4, check_person);
    add_exit(FOREST_DIR + "forest48", "east",0,4, check_person);
    add_exit(FOREST_DIR + "forest46", "west",0,4, check_person);
}

void reset_shire_room()
{
    set_searched(0);

}
