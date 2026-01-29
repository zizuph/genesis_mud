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

    add_exit(FOREST_DIR + "forest26", "north",0,4, check_person);

}

void reset_shire_room()
{
    set_searched(0);

}
