/*
 * fieldward/std/fieldward_room.c
 * Standard outdoor room for the Field Ward and northern outskirt areas
 *    of the City of Waterdeep
 *
 *  Created Jan 2021 by Brine
 */
#pragma strict_types

#include "../defs.h"
inherit WATERDEEP_ROOM;

#include "fieldward_roomdescs.o"

void
create_fieldward_room()
{
    set_short("Standard outdoor room for the Field Ward area");
    extraline = "Long description of the standard outdoor room for the Field "
        + "Ward area.\n";
    add_prop(IS_WATERDEEP_ROOM, 1);
}

void
create_waterdeep_room()
{
    create_fieldward_room();
}

void
setup_outskirt_room()
{
    add_waterdeep_outskirts();
    set_area(OUTSKIRTS);
    set_road_type(HIGH_ROAD);
}

void
setup_wall_room()
{
    add_in_waterdeep();
    set_area(TROLLWALL);
}

void
setup_fieldward_room()
{
    add_in_waterdeep();
    set_area(FIELD_WARD);
    set_road_type(FILTHY_STREET);
    add_strong_odour();
}

void
setup_fieldward_road_room()
{
    add_in_waterdeep();
    set_area(FIELD_WARD);
    set_road_type(HIGH_ROAD);
    add_weak_odour();
}
