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
    set_vbfc_extra(forest_desc6);
    add_item("chasm",
        "The chasm is deep and wide. It gapes before you as " +
        "it blocks your way here.\n");

    reset_shire_room();
    add_forest_herbs();

    add_exit(FOREST_DIR + "forest15", "north",0,4, check_person);
    add_exit(FOREST_DIR + "forest33", "southeast",0,4, check_person);
    add_exit(FOREST_DIR + "forest31", "southwest",0,4, check_person);

}

int
block()
{
    if (this_player()->query_wiz_level()) return 0;

        write("Long overhanging branches and thick underbrush " +
            "prevents you from going there\n");
    return 1;
}

void reset_shire_room()
{
    set_searched(0);

}
