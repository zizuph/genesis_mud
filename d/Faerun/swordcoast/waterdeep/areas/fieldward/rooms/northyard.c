/*
* fieldward/rooms/northyard.c
* This is the northyard, the main northern entrance into the city of Waterdeep
*
* Created Feb 2022 by Brine
*/

#pragma strict_types

#include "../defs.h"

inherit FIELDW_STD_ROOM;
// TODO: ADD PORTCULLIS!!!! (also in northgate)
void
create_fieldward_room()
{
    set_short("Northyard, inside the gate");
    set_extraline("Much placeholding.\n");

    add_exit(FIELDW_ROOM + "northgate", "north");
    add_exit(FIELDW_ROOM + "gatehouse01", "northwest");
    add_exit(FIELDW_ROOM + "gatehouse02", "northeast");
    add_exit(FIELDW_ROOM + "highroad01", "south");
}
