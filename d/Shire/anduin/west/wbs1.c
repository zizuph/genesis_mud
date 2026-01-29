/*
 * western riverbank of the river Anduin
 * By Finwe, June 2001
 */
 
#pragma strict_types
 
#include "local.h"

inherit VALE_BASE;

void
create_vale_room()
{
    set_area("along the riverbank of");
    set_areaname("the Anduin");
    set_land("the Vales of the Anduin");
    set_vbfc_extra(vale_desc8);
    set_areatype(0);
    add_my_desc("\n");

//    set_room_tell_time(random(ROOM_TELL_TIME) + 30);
    add_room_tell("A frog croaks in the bushes nearby.");
    add_room_tell("A fish jumps in the river.");
    add_room_tell("Something slaps the water with its tail.");
    add_room_tell("Quack, quack, quack.");
    add_room_tell("An animal slides into the water.");


    set_add_river_close();
    set_add_misty_near();
    reset_shire_room();

    add_exit(WEST_DIR + "wford", "north");
    add_exit(WEST_DIR + "wbs2", "south");
 
}

void reset_shire_room()
{
}
