#pragma strict_types

#include <stdproperties.h>

#include "/d/Khalakhor/ocean/defs.h"

inherit "/std/room";
inherit "/d/Khalakhor/ocean/lib";



/* This next function is essential when it comes to removing the drown 
   object. Imagine if one leaves a standard water room into an area with
   non-standard underwater rooms.. the drown object will stay, but it will
   not get removed if they then go to an ordinary room. */
int
query_standard_water_room ()
{
  return 0; 
}

int
block_me ()
{
  TP->catch_msg("A sturdy gate has been nailed shut, blocking your way "+
                "from the pier. You notice a group of goblins working "+
                "behind it.\n");
  return 1;
}

void
create_room ()
{
  set_short("On a pier near Daenbraigh.");

  set_long("You are standing on a thin patch of land west of the village " +
           "of Daenbraigh. Most of it looks like piles of sand and dirt "  +
           "heaved up next to the sea to provide a landing site for "      + 
           "transporting forces and goods between Daenbraigh and other "+
           "parts of Khalakhor and beyond.\n");

	add_item(({"sea" }),
           "The dark waters are swirling gently against the base of "+
           "the pier.\n");

  add_exit("pier-1-15-60", "east", block_me);
  
  add_row_exit(WASTELANDS_ENTRY, "west", no_go, 1);

  add_prop(ROOM_I_INSIDE, 0);
  add_prop(ROOM_I_TYPE, ROOM_NORMAL);

  // Set the sailing skill required to sail to this room.
  set_sailing_difficulty(NORMAL_DIFFICULTY);

  // Set the optional message when sailing into this room.
  set_sailing_fail_message("You feel uncomfortable departing even these "+
                           "strange lands of Daenbraigh.\n");
  set_sailing_difficulty_message("You navigate across the protected " +
                                 "waters surrounding Daenbraigh!\n");
}

