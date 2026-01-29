/*
 * fieldward/std/fieldward_room_indoor.c
 * Standard indoor room for the Field Ward and northern outskirt areas
 *    of the City of Waterdeep
 *
 *  Created Jan 2021 by Brine
 */
#pragma strict_types

#include "../defs.h"

inherit WATERDEEP_INDOOR;

#include "fieldward_roomdescs.o"

void
create_fieldward_indoor_room()
{
  // Redefine this function
  set_short("Standard indoor room for the Field Ward area");
  extraline = "Long description of the standard indoor room for the Field "
    + "Ward area.\n";
}

void
create_waterdeep_indoor_room()
{
  create_fieldward_indoor_room();
}
