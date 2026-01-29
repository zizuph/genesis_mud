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

    add_exit(FOREST_DIR + "forest54", "east",0,4, check_person);    
    add_exit(FOREST_DIR + "forest52", "west",0,4, check_person);
    add_exit(FOREST_DIR + "forest63", "southeast",0,4, check_person);
}

void reset_shire_room()
{
}
