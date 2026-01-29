/*
 * Road in Bree
 * By Finwe, June  2001
 */
 
#pragma strict_types
//#include "/d/Shire/common/lib/herbsearch.h"

#include "/d/Shire/sys/defs.h" 
#include "defs.h"

inherit ROAD_BASE;


void
create_road_room()
{   
    setuid();
    seteuid(getuid());

    set_add_orchard();

    apples = 0;
    set_areadesc("southeast");
    set_area("corner in");
    set_areaname("the orchard");
    set_land("Bree");
    add_my_desc("\n");

    add_exit(ROAD_DIR + "orchard03", "north");
    add_exit(ROAD_DIR + "broad13", "east");
    add_exit(ROAD_DIR + "orchard02", "west");

    reset_shire_room();


}

void
init()
{
    add_action("sniff_air", "sniff");
    add_action("sniff_air", "smell");
    add_action("get_apple", "get");
    add_action("get_apple","pick");
    ::init();
}
