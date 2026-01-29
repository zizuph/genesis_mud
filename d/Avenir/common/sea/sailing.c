/* Avenir's sailing file is a copy of Khalakhor's:
 * /d/Khalakhor/ocean/sailing.c
 * Based off Sparkle code /d/Sparkle/area/sea/std_sailing_room.c
 * Based off sailing room code /d/Krynn/std/sail_room_base.c
 * Tapakah, 10/2021
 */

#pragma strict_types

#include <macros.h>
#include <stdproperties.h>
#include <language.h>
#include <ss_types.h>
#include <macros.h>
#include <formulas.h>
#include <composite.h>

// Includes mariner standardised sailing code
#include "defs.h"

inherit "/std/room";
inherit SAILING_LIB;

#define CREATE "create_sea_room"
#define RESET "reset_sea_room"

/* Redefine if you use the std_sailing_room for a lake or freshwater
   river to "freshwater". See /d/Krynn/common/fishing/
*/

string
query_fishing_area ()
{
  return "saltwater";
}


/*
 * IN NORMAL CASES YOU SHOULDN'T NEED TO CHANGE ANYTHING BELOW
 */

nomask int
query_reset ()
{
  return function_exists(RESET, TO) ? 1 : 0;
}

void
create_room ()
{
  call_other(TO, CREATE);

  set_sink_path(SEA_ROOM + "sink_room");  
}
