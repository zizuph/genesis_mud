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
    set_short("Along a chasm deep in the forest");
    set_vbfc_extra(forest_desc6);
    add_item("chasm",
        "The chasm is deep and wide. It gapes before you as " +
        "it blocks your way here.\n");
    reset_shire_room();

    add_exit(FOREST_DIR + "forest64", "north",0,4, check_player(0));
    add_exit(FOREST_DIR + "forest72", "east",0,4, check_player(0));
    add_exit(FOREST_DIR + "forest65", "northeast",0,4, check_player(2));
    add_exit(FOREST_DIR + "forest75", "southwest",0,4, check_player(2));


}

