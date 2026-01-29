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

    add_exit(FOREST_DIR + "forest55", "north","@@block_me@@",4, 1);
    add_exit(FOREST_DIR + "forest71", "south",0,4, check_person);
    add_exit(FOREST_DIR + "forest54", "northwest",0,4, check_person);

}

int
block_me()
{
    if (this_player()->query_wiz_level()) return 0;
    write("Thick underbrush blocks you, preventing you from " +
		"going that way.\n");
    return 1;
}

void reset_shire_room()
{
}
