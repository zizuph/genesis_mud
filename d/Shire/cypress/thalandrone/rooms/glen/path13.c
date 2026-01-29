/*
 * Forest path leading to Wild Elves Guild
 * By Finwe, July 2001
 */
 
#pragma strict_types
#include "/d/Shire/cypress/sys/defs.h" 
#include "/d/Shire/cypress/thalandrone/local.h"

//inherit "/d/Shire/cypress/thalandrone/base_road.c";
inherit FOREST_BASE;

//string road_type = "path";

void
create_forest_room()
{
    set_vbfc_extra(road_desc4);

    add_my_desc("The "+road_type+" runs northwest into a small " +
    "dale and east into the forest.\n");
    
    add_exit(GLEN_DIR + "path12", "northwest");
    add_exit(GLEN_DIR + "path14", "east");
    reset_room();
}

void
reset_room()
{
/*
    object leaf;

    seteuid(getuid());
    
    if (!present("_shire_leaf_",TO))
    {
        leaf = clone_object("/d/Shire/scav_hunt/leaf");
//        fish_skeleton->add_prop(OBJ_I_HIDE, 10 + random(10));
        leaf->move(TO);
    }
*/
}
