/*
 * cadu_b2.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 * Ported to the new ship system by Tapakah, 10/2008
 */

#pragma save_binary
#pragma strict_types

#include <stdproperties.h>
#include <macros.h>
#include "../defs.h"
#include "/d/Genesis/gsl_ships/ships.h"

inherit "/std/room";
inherit STDPIER;

void
create_room()
{
  ::create_pier();
  set_short("Pier to Sparkle.");
  set_long("You are on the pier south of Cadu.\n" +
           "This is where the boat to Sparkle lands. " +
           "To the north the pier continues towards land " +
           "and to the west there seems to be some kind " +
           "of tower on the pier. To the east the pier abruptly " +
           "drops off, and the sea crashes up against it.\n");
  
  add_exit("cadu_b4", "north");
  add_exit("cadu_b3","west");
  
  add_item("tower", "The tower is too far west to be properly examined.\n");
  
	add_pier_entry(MASTER_OB(TO), "Cadu", "Ship to Sparkle");
	initialize_pier();
  BEACH;
}
