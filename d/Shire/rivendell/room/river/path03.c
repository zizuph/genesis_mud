/*
 * Shore of river Bruinen
 * By Finwe, August 1998
 */
 
#pragma strict_types
#include "/d/Shire/sys/defs.h" 
#include "local.h"
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
 
inherit SHORE_BASE;

void
create_shore_room()
{

//    set_area("path");
    set_areaname("a dark forest");
    set_land("Eriador");
    set_areatype(0);
    set_areadesc("rocky path");
    set_grass("sparse, dry");
    set_treetype("conifer");

    set_extraline("Thick, heavy branches hang over you and the river. " +
        "They cast long shadows over the land and block most of the light. " +
        "A forest runs along the river bank. It is dark and looks formidable.");
    
    add_item(({"path", "rocky path"}),
        "The path is rocky and made from river stones. It leads into the " +
        "forest and towards the river.\n");
    add_item(({"stones", "river stones"}),
        "The river stones are oval and smooth. They are all sizes and colors.\n");

    add_exit(FOREST_DIR + "forest75", "northeast",0,4);
    add_exit(RIVER_DIR  + "path02", "west",0,4);

    reset_shire_room();

}

void
reset_shire_room()
{
}


