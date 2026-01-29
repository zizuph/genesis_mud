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
block_mountains ()
{
  TP->catch_msg("The steep mountains surrounding the Nexus are simply "+
                "impassable from this side.\n");
  return 1;
}

int
block_hh ()
{
  TP->catch_msg("As you approach the grove, two bulky figures wielding "+
                "heavy mattocks step out and thunder: 'We are not open "+
                "just yet'.\n");
  return 1;
}

int block_steppe ()
{
  TP->catch_msg("A recent rain turned this part of the steppe into a "+
                "large swamp that is not possible to cross. You will "+
                "have to wait until it dries up.\n");
  return 1;
}

void
create_room ()
{
  set_short("In a forest clearing on a shore in southwestern Khalakhor");

  set_long("You are on a small clearing on a rocky shore somewhere quite "+
           "close the Nexus along the southeastern side of Khalakhor. "+
           "The cobalt blue sea is pushing low waves to the shore, not "+
           "particularly threatening, but not calm at all. You can see "+
           "the steep mountains surrounding the Nexus just to your east, "+
           "while a wide steppe begins to your south. To the southwest "+
           "a grove of trees has an opening into it, with two strange "+
           "branches resembling fists on a hammer handle crossing above "+
           "it.\n");

	add_item(({"sea" }),
           "The cobalt blue waters are coming in small waves at the shore.\n");

  add_exit("mountains-25-13", "west", block_mountains);
  add_exit("hhands-25-14", "southwest", block_hh);
  add_exit("steppe-26-14", "south", block_steppe);
  
  add_row_exit(HAMMERHANDS_ENTRY, "north", no_go, 1);

  add_prop(ROOM_I_INSIDE, 0);
  add_prop(ROOM_I_TYPE, ROOM_NORMAL);

  // Set the sailing skill required to sail to this room.
  set_sailing_difficulty(NORMAL_DIFFICULTY);

  // Set the optional message when sailing into this room.
  set_sailing_fail_message("You feel uncomfortable departing this "+
                           "quiet landing.\n");
  set_sailing_difficulty_message("You navigate across the calm " +
                                 "southeast shores of Khalakhor!\n");
}

