/*
 * Road in the Barrow Downs
 * By Finwe, December 2001
 */
 
#pragma strict_types
 
#include "../local.h"

inherit ROAD_BASE;

 
void
create_road_room()
{
    set_areadesc("path");
    set_area("somewhere in");
    set_areaname("the Barrow Downs");
    set_land("Eriador");

    set_vbfc_extra(road_desc3);
    set_extraline("Barrows rise in the distance, hidden by the " +
        "fogs and mists. Below the barrow, a river flows west " +
        "into the Old Forest.");
    set_add_wight_sounds();

    clone_object(DOWNS_OBJ + "cairn")->move(this_object(), 1);
    set_stone_num("/d/Shire/downs/obj/stone06");

    add_exit(ROAD_DIR + "road19", "southwest");
    add_exit(ROAD_DIR + "road12", "north");

}

public void init()
{
    ::init();
    add_action( "do_dig", "dig");
}
