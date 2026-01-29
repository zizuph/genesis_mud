/*
 * Barrow #1
 * By Finwe, December 2001
 */
 
#pragma strict_types
 
#include "local.h"

inherit ROAD_BASE;
/* The stone number players are moved to. 
 * Corresponds to the barrow number they dig into.
 */
//string stone_num = "/d/Shire/obj/stone01";   

 
void
create_road_room()
{
    set_areadesc("path");
    set_area("somewhere in");
    set_areaname("the Barrow Downs");
    set_land("Eriador");

    set_vbfc_extra(road_desc1);
    set_extraline("The path splits and runs southwest and southeast " +
        "deeper into the Downs as well as northwest out out of " +
        "the area.");
    set_add_wight_sounds();

    clone_object(DOWNS_OBJ + "cairn")->move(this_object(), 1);
    set_stone_num("/d/Shire/downs/obj/stone01");

    add_exit(DOWNS_DIR + "road08", "southwest");
    add_exit(DOWNS_DIR + "road09", "southeast");
    add_exit(DOWNS_DIR + "road05", "northwest"); 
}

public void init()
{
    ::init();
    add_action( "do_dig", "dig");
}
