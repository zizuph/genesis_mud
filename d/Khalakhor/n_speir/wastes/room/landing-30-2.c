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
  TP->catch_msg("A large crack in the ground with the hot lava flowing "+
                "through it prevents you from leaving this room.\n");
  return 1;
}

void
create_room ()
{
  set_short("On a clearing in the wasteland.");

  set_long("You are standing in a small clearing of stony ground in "+
           "the very north of Khalakhor. You can hear the underground "+
           "rumbles and the volcanic explosions, and you see rivers of "+
           "red and orange flowing through the black land. This "+
           "particular piece of land seems safe for the time being "+
           "though.\n");

	add_item(({"sea" }),
           "The midnight-black waters are crashing against the landing.\n");

  add_exit("waste-30-3", "south", block_me);
  
  add_row_exit(WASTELANDS_ENTRY, "north", no_go, 1);

  add_prop(ROOM_I_INSIDE, 0);
  add_prop(ROOM_I_TYPE, ROOM_NORMAL);

  // Set the sailing skill required to sail to this room.
  set_sailing_difficulty(ROUGH_SEAS_DIFFICULTY);

  // Set the optional message when sailing into this room.
  set_sailing_fail_message("You feel uncomfortable departing even this "+
                           "wretched piece of land into the torrents of "+
                           "the northern Khalakhor seas.\n");
  set_sailing_difficulty_message("You navigate across the torrents " +
                                 "of the northern Khalakhor seas!\n");
}

