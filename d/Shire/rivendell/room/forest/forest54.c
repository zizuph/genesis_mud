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
    set_vbfc_extra(forest_desc1);
    reset_shire_room();
    add_forest_herbs();

    add_exit(FOREST_DIR + "track01", "north",0,4, check_person);
    add_exit(FOREST_DIR + "forest55", "east",0,4, check_person);
    add_exit(FOREST_DIR + "forest53", "west",0,4, check_person);
    add_exit(FOREST_DIR + "forest64", "southeast",0,4, check_person);
}

int
block_me()
{
    if (this_player()->query_wiz_level()) return 0;
    write("The trees block you from going that way.\n");
    return 1;
}

void reset_shire_room()
{
    set_searched(0);

}
