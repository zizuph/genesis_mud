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

    add_exit(FOREST_DIR + "forest13", "north",0,4, check_person);
    add_exit(FOREST_DIR + "forest22", "east","@@block",4, check_person);
    add_exit(FOREST_DIR + "forest29", "southwest",0,4, check_person);
}

int
block()
{
    if (this_player()->query_wiz_level()) return 0;

        write("Trees have grown together and prevent you from " +
		"going that way.\n");
    return 1;
}

void reset_shire_room()
{
}
