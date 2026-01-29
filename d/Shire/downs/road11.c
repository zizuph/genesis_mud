/*
 * Barrow #3
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

    set_vbfc_extra(road_desc1);
    set_extraline("");

    clone_object(DOWNS_OBJ + "cairn")->move(this_object(), 1);
    set_stone_num("/d/Shire/downs/obj/stone03");

    add_exit(DOWNS_DIR + "road10", "west");
    add_exit(DOWNS_DIR + "road12", "east");

}

public void init()
{
    ::init();
    add_action( "do_dig", "dig");
}
