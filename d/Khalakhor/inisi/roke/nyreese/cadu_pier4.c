/*
 * New pier - Line to Eil Galaith isle
 * Tapakah, 04/2009
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
  set_short("Pier to Eil Galaith");
  set_long("You are on the pier south of Cadu.\n" +
           "This is where the ship to the elven island of Eil Galaith lands. " +
           "To the north, across the water you can see the beaches of Cadu " +
           "and to the southwest there seems to be some kind " +
           "of tower on the pier. To the west you see some kind of stall " +
           "and to the east it the pier continues. "+
           "To the far west you see a new building.\n");

  add_exit("cadu_pier_toilet", "west");
  add_exit("cadu_pier5","east");
  
  add_item("tower", "The tower is too far west to be properly examined.\n");
  
  add_pier_entry(MASTER_OB(TO), "Cadu", "Line to Eil Galaith");
  initialize_pier();
  BEACH;
}
