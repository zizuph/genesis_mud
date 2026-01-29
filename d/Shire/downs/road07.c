/*
 * Barrow #2
 * By Finwe, December 2001
 */
 
#pragma strict_types
 
#include "local.h"

inherit ROAD_BASE;

 
void
create_road_room()
{
    set_areadesc("path");
    set_area("somewhere in");
    set_areaname("the Barrow Downs");
    set_land("Eriador");

    set_vbfc_extra(road_desc3);
    set_extraline("The barrows appear as bumps in the mists, some " +
        "crowned with stone monuments. The path wanders east and " +
        "southwest between the hills. From somewhere, a river " +
        "courses past the barrows as it flows southwest toward " +
        "the Old Forest.");
    set_add_wight_sounds();  

    clone_object(DOWNS_OBJ + "cairn")->move(this_object(), 1);
    set_stone_num("/d/Shire/downs/obj/stone02");
    
    add_exit(DOWNS_DIR + "road12", "southwest");
    add_exit(DOWNS_DIR + "road08", "east"); 
}

public void init()
{
    ::init();
    add_action( "do_dig", "dig");
}
