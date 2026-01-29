 /* /d/Cirath/ships/kalad/kalad_port.c
  * A 'water' room for the Tyr-Kalad line to run through.
  * Decius, November 1996
  */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
#include "ship.h"

void
create_room()
{
  set_short("The Great Kalad Waste");
  set_long("The Great Kalad Waste, a desert of immense "+
    "proportions surrounds you from all diretions. The "+
    "ever-present swirling sand, coupled with the harsh "+
    "Kaladian sun only further enhances the utter "+
    "bleakness of this landscape. This appears to be some "+
     "sort of gathering spot for caravans of all types. A "+
     "place to trade goods from the mundane to the rarest "+
     "of valuables. Strange lizard beasts pull huge wagons "+
     "here from the east, departing in that direction when "+
    "their business is done with the nomad traders.\n"+
    "There is a sign here.\n");

  add_item("sign","The wooden sign can be read.\n");
  add_cmd_item("sign","read","I Kokor will take upon my "+
     "caravan anyone wishing passage to the city of Tyr, "+
     "for the price of 30 coppers.\n");

  OUTSIDE;
  ADD_SUN_ITEM;
  add_exit("/d/Kalad/common/wild/pass/desert/d3.c","west",0,1,0);
}
