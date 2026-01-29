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

    add_exit(FOREST_DIR + "forest49", "south",0,4, check_person);
    add_exit(FOREST_DIR + "forest40", "west",0,4, check_person);
    add_exit(FOREST_DIR + "forest48", "southwest",0,4, check_person);

}
