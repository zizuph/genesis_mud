/*
* fieldward/rooms/highroad01.c
* A room in the field ward of Waterdeep
*
* Created Feb 2022 by Brine
*/

#pragma strict_types

#include "../defs.h"

inherit FIELDW_STD_ROOM;

void
create_fieldward_room()
{
    set_short("Highroad, main square");
    set_extraline("Such place. Much holding. Wow.\n");

    add_exit(FIELDW_ROOM + "northyard", "north");
    add_exit(FIELDW_ROOM + "fieldway01", "west");
    add_exit(FIELDW_ROOM + "gawenknife_st01", "southeast");
    add_exit(FIELDW_ROOM + "highroad02", "south");
}
