/*
 * Road in Bree
 * By Finwe, June  2001
 */
 
#include "/d/Shire/sys/defs.h" 
#include "defs.h"

inherit ROAD_BASE;

object sonic;

void make_npcs();

void
create_road_room()
{
    set_areadesc("large busy road");
    set_area("alongside");
    set_areaname("houses and hobbit holes");
    set_land("Bree");

    add_my_desc("It runs north and south and follows a stone wall " +
        "to the west. Houses are replaced with hobbit holes dug into " +
        "the side of the hill.\n");

    set_add_houses();
    set_add_hobbit_holes();
    set_add_outside_smiths();
    set_add_hill();

    make_npcs();

    add_exit(ROAD_DIR + "broad21", "north");
    add_exit(ROAD_DIR + "broad07", "south");
}

reset_shire_room()
{
    make_npcs(); 
}


void
make_npcs()
{
   if(!sonic)
   {
    sonic = clone_object(NPC_DIR + "sonic.c");
    sonic->move(TO);
    tell_room(TO,capitalize(LANG_ADDART(sonic->query_nonmet_name())) + 
        " comes sobbing into the room.\n");
    }
}

