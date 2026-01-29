/*
* fieldward/rooms/endshift_inn.c
* The Endshift Inn in the field ward of Waterdeep, where the city guards come
* to drink after their shifts are ended
*
* Created May 2022 by Brine
*/

#pragma strict_types

#include "../defs.h"

inherit FIELDW_STD_INDOOR;

void
create_fieldward_indoor_room()
{
    set_short("The Endshift Inn");
    set_long("Such place. Much holding. Wow.\n");

    add_exit(FIELDW_ROOM + "endshift_st", "out");
}
