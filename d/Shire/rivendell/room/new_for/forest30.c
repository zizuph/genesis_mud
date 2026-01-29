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

    set_add_white_stone("bottom", "left-side");

    add_exit(FOREST_DIR + "forest37", "south",0,4, check_person);
    add_exit(FOREST_DIR + "forest29", "west",0,4, check_person);
    add_exit(FOREST_DIR + "forest22", "northeast",0,4, check_person);

}

void reset_shire_room()
{
}
