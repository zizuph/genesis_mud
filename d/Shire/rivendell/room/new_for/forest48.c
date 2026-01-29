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
    set_vbfc_extra(forest_desc4);
    reset_shire_room();

    add_exit(FOREST_DIR + "forest40", "north",0,4, check_player(2));
    add_exit(FOREST_DIR + "forest47", "west",0,4, check_player(0));
    add_exit(FOREST_DIR + "forest41", "northeast",0,4, check_player(0));
    add_exit(FOREST_DIR + "forest57", "southwest",0,4, check_player(2));

}

void reset_shire_room()
{
}
