/*
 * Forest near Rivendell
 * By Finwe, August 1998
 */
 
#pragma strict_types
 
#include "local.h"
#include "/d/Shire/sys/defs.h"
#include "/d/Shire/guild/noldor/noldor.h"

 
inherit FOREST_BASE;

int check_players = 1;
 
void
create_forest_room()
{
    set_vbfc_extra(forest_desc2);
    reset_shire_room();
    add_forest_herbs();

    add_exit(FOREST_DIR + "forest24", "northeast",0,4, check_person);
    add_exit(FOREST_DIR + "track02", "south",0,4, check_person);
    add_exit(FOREST_DIR + "forest38", "southwest",0,4, check_person);


}

int
block_me()
{
    if (this_player()->query_wiz_level() || IS_MEMBER(TP)) return 0;
    write("The trees block you from going that way.\n");
    return 1;
}

void reset_shire_room()
{
    set_searched(0);

}
