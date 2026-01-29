/*
 * New pier - Line to SaMorgan
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
  set_short("Pier to SaMorgan");
  set_long("You are on the pier south of Cadu.\n" +
           "This is where the ship to the elven town of Sa Morgan lands."+
           "To the north, across the water you can see the beaches of Cadu " +
           "and to the southwest there seems to be some kind " +
           "of tower on the pier. To the east and west you see some kind "+
           "of stalls and beyond them the pier continues. "+
           "To the far west you see a new building.\n");

  add_exit("cadu_pier_drink", "west");
  add_exit("cadu_pier_toilet","east");
  
  add_item("tower", "The tower is too far west to be properly examined.\n");
  
  add_pier_entry(MASTER_OB(TO), "Cadu", "Line to Sa Morgan");
  initialize_pier();
  BEACH;
}
