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
    set_vbfc_extra(forest_desc2);
    reset_shire_room();

    add_exit(FOREST_DIR + "forest36", "northwest",0,4, check_person);
    add_exit(FOREST_DIR + "forest52", "southwest",0,4, check_person);
    add_exit(FOREST_DIR + "forest38", "northeast",0,4, check_person);

}

void reset_shire_room()
{
}
