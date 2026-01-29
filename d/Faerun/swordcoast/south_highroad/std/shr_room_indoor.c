/*
 * south_highroad/std/shr_room_indoor.c
 * Standard indoor room for the Southern High Road and the outskirts of the
 * City of Waterdeep
 *
 *  Created Jan 2021 by Brine
 */
#pragma strict_types

#include "../defs.h"
inherit FAERUN_INDOORS_BASE;

void
create_shr_indoor_room()
{
  set_short("Standard indoor room for the Southern High Road area");
  extraline = "Long description of the standard indoor room for the Southern "
   + "High Road area.\n";
}

void
create_indoor_room()
{
  create_shr_indoor_room();
}
