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
block_shore ()
{
  TP->catch_msg("The jagged rocks on the shore are simply impassable.\n");
  return 1;
}

int
block_forest ()
{
  TP->catch_msg("As you approach the forest, the branches and the leaves "+
                "sway towards you, shooing you away. You swear you saw a tall "+
                "shape in a long robe behind them, which could have been an elf "+
                "or a human. You get a feeling that later this forest might "+
                "become more welcome, though.\n");
  return 1;
}

void
create_room ()
{
  set_short("In a forest clearing on a shore in southwestern Khalakhor");

  set_long("You are on a small clearing on a rocky shore somewhere mid-way "+
           "up to the Nexus along the southwestern side of Khalakhor. "+
           "The sea is of a darker hue, calm, but fast swirling for some "+
           "reason. The rocks have been cleared from this spot, but it is "+
           "not clear, if it was a living's work, or a natural occurrence. "+
           "On land you are surrounded by the rocky shore and the dark "+
           "broadleaf forest.\n");

	add_item(({"sea" }),
           "The lapis lazuli waters are swirling around the shore rocks.\n");

  add_exit("forest-11-10", "east", block_forest);
  add_exit("forest-10-11", "south", block_forest);
  add_exit("shore-9-11", "southwest", block_shore);
  add_exit("shore-11-9", "northeast", block_shore);
  
  add_row_exit(DRUID_ENTRY, "north", no_go, 1);

  add_prop(ROOM_I_INSIDE, 0);
  add_prop(ROOM_I_TYPE, ROOM_NORMAL);

  // Set the sailing skill required to sail to this room.
  set_sailing_difficulty(NORMAL_DIFFICULTY);

  // Set the optional message when sailing into this room.
  set_sailing_fail_message("You feel uncomfortable departing this quiet "+
                           "landing.\n");
  set_sailing_difficulty_message("You navigate across the calm " +
                                 "southwest shores of Khalakhor!\n");
}

