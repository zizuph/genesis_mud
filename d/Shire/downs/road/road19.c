/*
 * Barrow #8
 * By Finwe, March 2001
 */
 

#include "../local.h"

inherit ROAD_BASE;

/* The stone number players are moved to. 
 * Corresponds to the barrow number they dig into.
 */

void
create_road_room()
{
    set_areadesc("path");
    set_area("somewhere in");
    set_areaname("the Barrow Downs");
    set_land("Eriador");

    set_vbfc_extra(road_desc2);
    set_extraline("The path crests the barrow, stopping at a cairn.");
    set_add_wight_sounds();

    clone_object(DOWNS_OBJ + "cairn")->move(this_object(), 1);
    set_stone_num("/d/Shire/downs/obj/stone08");

    add_exit(ROAD_DIR + "road15", "northeast");

}

public void init()
{
    ::init();
    add_action( "do_dig", "dig");
}
