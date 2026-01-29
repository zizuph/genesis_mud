/*
 * Pier for mariners in Galaith Isle
 * Based on Jetty in Sparkle by Arman
 * Tapakah, 10/2021
 *
 */

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

void
create_room ()
{
  set_short("On the new pier");

  set_long("You are on the freshly constructed extension to the pier of " +
           "the isle of Galaith. It was built to facilitate the chartered ships " +
           "of Genesis from the lands far beyond.\n");


  add_item(({"pier", "wood" }),
           "The impressive pier is in extremely good shape and feels "+
           "very sturdy and safe.\n");
	add_item(({"sea" }),
           "The calm waters surrounding the Galaith Isle lap gently "+
           "at the wooden construction of the pier.\n");

  add_exit("pier2","north");
  add_row_exit(GALAITH_ENTRY, "west", no_go, 1);

  add_prop(ROOM_I_INSIDE, 0);
  add_prop(ROOM_I_TYPE, ROOM_NORMAL);

  // Set the sailing skill required to sail to this room.
  set_sailing_difficulty(NORMAL_DIFFICULTY);

  // Set the optional message when sailing into this room.
  set_sailing_fail_message("The unskilled hands cannot navigate even the " +
                           "calm waters around Galaith.\n");
  set_sailing_difficulty_message("You navigate along the shores " +
                                 " of the Galaith Isle!\n");
}

