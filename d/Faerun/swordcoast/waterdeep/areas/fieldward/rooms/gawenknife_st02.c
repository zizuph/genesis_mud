/*
* fieldward/rooms/gawenknife_st02.c
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
    set_short("On Gawenknife Street");
    set_extraline("Such place. Much holding. Wow.\n");

    add_exit(FIELDW_ROOM + "gawenknife_st01", "west");
    add_exit(FIELDW_ROOM + "gawenknife_st03", "southeast");
}
