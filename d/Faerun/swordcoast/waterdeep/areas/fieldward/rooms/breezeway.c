/*
* fieldward/rooms/breezeway.c
* On Gawenknife Street in the field ward of Waterdeep
*
* Created Feb 2022 by Brine
*/

#pragma strict_types

#include "../defs.h"

inherit FIELDW_STD_ROOM;

void
create_fieldward_room()
{
    set_short("On the Breezeway");
    set_extraline("Such place. Much holding. Wow.\n");

    add_exit(FIELDW_ROOM + "endshift_st", "northwest");
}
