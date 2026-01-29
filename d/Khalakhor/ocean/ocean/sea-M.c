/*
 * Sector M -  Miath Rae, sea around SW speir 
 * Tapakah, 10-11/2021
 */

#pragma strict_types

#include <ss_types.h>
#include "defs.h"

inherit SEA_SECTOR;

string
long_descr ()
{
  string descr =
    "You are sailing along the blue-green waters of Miath Rae, " +
    "which surrounds the southwestern speir of the Khalakhor mainland.\n";

  mixed *ddp;
  
  if (TP->query_skill(SS_LOC_SENSE) > 30) {
    ddp = get_distance_direction(Xx, Yy, "Sa Morgan");
    descr += "You guess the village of Sa Morgan is somewhere to your " + ddp[1] +
      ".\n";
  }
  return descr;
}

string
get_continents ()
{
  return
    "You can see the coasts of the southwestern speir of "+
    "Khalakhor at some distance. " +
    "You will need to get closer to them to find a good spot for "+
    "a landfall.\n";
}

void
create_sea_room ()
{
  ::create_sea_sector("Miath Rae", TRICKY_DIFFICULTY);
  
  add_item(({"sea", "ocean", "water"}),
           "The waters of Miath Rae shine in the bright turquoise. "+
           "White sheep-like clusters of foam merrily ride the smooth "+
           "waves, making the ship rock gently sideways, without making "+
           "you feel threatened.\n");
}
