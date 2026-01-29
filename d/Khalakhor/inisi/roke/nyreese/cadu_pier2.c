/*
 * New pier - Newbie line
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
  set_short("Pier to Port Macdunn");
  set_long("You are on the pier south of Cadu.\n" +
           "This is from where the ship to Port Macdunn departs. " +
           "To the north, across the water you can see the beaches of Cadu " +
           "and to the southwest there seems to be some kind " +
           "of tower on the pier. To the east and west you see some kind "+
           "of stalls and beyond them the pier continues. "+
           "A bit more far away to the west you see a new building.\n");

  add_exit("cadu_pier_food", "west");
  add_exit("cadu_pier_drink", "east");
  
  add_item("tower", "The tower is too far west to be properly examined.\n");
  
  add_pier_entry(MASTER_OB(TO), "Cadu", "Line to Port Macdunn");
  initialize_pier();
  BEACH;
}
