/*
 * waterdeep/std/waterdeep_room.c
 * Waterdeep standard room
 *
 * 2021/01: Created by Brine
 */
#pragma strict_types

#include "../defs.h"
inherit FAERUN_INDOORS_BASE;

#include "waterdeep_room_flair.o"

void
create_waterdeep_indoor_room()
{
  // This function will likely be shadowed in higher level std rooms, and
  // the statements below will have to be included in those std rooms in
  // some form.
  set_short("This is the standard Waterdeep indoor room");
  extraline = "\nLong indoor room description.\n";

  add_prop(IS_WATERDEEP_ROOM, 1);
}

void
create_indoor_room()
{
  create_waterdeep_indoor_room();
}
