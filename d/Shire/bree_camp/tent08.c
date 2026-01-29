/*
 * Inside tent in Bree orc camp
 * By Finwe, July 2000
 */
 
#pragma strict_types
 
#include "local.h"
#include "/d/Shire/orcmaker/orcmaker.h"
#include <language.h>
inherit TENT_BASE;
inherit CAMP_DIR + "bree_orcs"; 
#define TENT_EXIT CAMP_DIR + "path08"
 
void
create_tent_room()
{
    add_my_desc("Crudely constructed furniture lies scattered " +
        "about the tent. Debris is piled in heaps throughout " +
        "the tent.\n");
 
    add_exit(TENT_EXIT, "out");
    reset_shire_room();
 
    furniture();
    chairs();
    table();
}
 
void reset_shire_room()
{
    clone_tent_orcs();
}

