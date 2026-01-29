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
  set_short("Pier for the newbie line (unused)");
  set_long("You are on the pier south of Cadu.\n" +
           "This is where the newbie line is going to land. " +
           "To the north the pier continues towards land " +
           "and to the southwest there seems to be some kind " +
           "of tower on the pier. To the east you see some kind of stall " +
           "and beyond it the pier continues. "+
           "To the west you see a new building.\n");

  add_exit("cadu_pier_food", "east");
  add_exit("cadu_b4","west");
  
  add_item("tower", "The tower is too far west to be properly examined.\n");
  
  add_pier_entry(MASTER_OB(TO), "Cadu", "Newbie Circle via Cadu");
  initialize_pier();
  BEACH;
}
