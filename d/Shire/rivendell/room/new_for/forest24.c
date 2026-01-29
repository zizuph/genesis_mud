/*
 * Forest near Rivendell
 * By Finwe, August 1998
 */
 
#pragma strict_types
 
#include "local.h"
#include "/d/Shire/guild/noldor/noldor.h"

 
inherit FOREST_BASE;

int check_players = 1;
 
void
create_forest_room()
{
    set_vbfc_extra(forest_desc4);
    reset_shire_room();

    add_exit(FOREST_DIR + "forest16", "north",0,4, check_person);
    add_exit(FOREST_DIR + "track05", "east","@@block@@",4, check_person);
    add_exit(FOREST_DIR + "forest32", "southwest",0,4, check_person);
    add_exit(FOREST_DIR + "track06", "northeast",0,4, check_person);

}

int
block()
{
    if (this_player()->query_wiz_level() || IS_MEMBER(TP)) return 0;
        write("An ancient tree has fallen across the path, " +
		"preventing travellers from going that way.\n");
    return 1;
}

void reset_shire_room()
{
}
