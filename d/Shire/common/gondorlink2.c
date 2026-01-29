/*
 * western riverbank of the river Anduin
 * By Finwe, June 2001
 */
 
#pragma strict_types
 
#include "/d/Shire/anduin/local.h"

inherit VALE_BASE;

void create_vale_room()
{
    set_area("along the Anduin in");
    set_areaname("northern Ithilien");
    set_land("Gondor");
    set_vbfc_extra(vale_desc6);
    set_areatype(0);
    add_my_desc(" \n");

//    set_room_tell_time(random(ROOM_TELL_TIME) + 30);
    add_room_tell("A frog croaks in the reeds nearby.");
    add_room_tell("A fish jumps in the river.");
    add_room_tell("Something slaps the water with its tail.");
    add_room_tell("Somewhere in the grass you hear: Quack, quack, quack.");
    add_room_tell("An animal slides into the water.");

    set_add_river_close();
    set_add_misty_near();

    add_exit(WEST_DIR + "wbs5", "north");
    add_exit("/d/Gondor/common/shirelink2", "southeast");

 
}
