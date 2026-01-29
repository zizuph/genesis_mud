/*
* fieldward/rooms/fieldway05.c
* On the fieldway in the field ward of Waterdeep
*
* Created Feb 2022 by Brine
*/

#pragma strict_types

#include "../defs.h"

inherit FIELDW_STD_ROOM;

void
create_fieldward_room()
{
    set_short("On the fieldway");
    set_extraline("Such place. Much holding. Wow.\n");

    add_exit(FIELDW_ROOM + "fieldway04", "southeast");
    add_exit(FIELDW_ROOM + "trollyard", "west");
}
