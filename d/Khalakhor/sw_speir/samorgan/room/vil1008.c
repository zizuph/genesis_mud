/**********************************************************************
 * - vil1007.c                                                      - *
 * - Village room.                                                  - *
 * - Created by Damaris@Genesis 02/2005                             - *
 * - added exit to the guard tower, Tapakah 04/2021                 - *
 **********************************************************************/
#pragma strict_types

#include "../defs.h"

inherit SAMORGAN_BASE;

void
create_khalakhor_room()
{
  set_xlong("A tower has been constructed at "+
            "the southeastern point of the village.\n");
  config_room("southern");
  
  add_item("northwest", "There is a building in that direction.\n");
  add_item("north", "There is a tavern in that direction.\n");
  add_item("east", "There is a tower in that direction.\n");
 
  add_item(({"west", "northeast"}),
           "The street continues in that direction.\n");
  add_item(({"southeast", "southwest", "south", "east"}),
           "There is a rocky beach in that direction.\n");
  add_item(({"tower", "guard tower"}),
           "A two-level guard tower has been constructed at the "+
           "southeastern point of the village.\n");
 
  add_exit("pub", "north");
  add_exit("vil1007", "west");
  add_exit("tower-se", "east");
  add_exit("vil0909", "northeast");
  
  add_fail("northwest", "A building blocks your passage.\n");
  add_fail("southeast", "The pier is under construction at this time.\n");
  add_fail(({"south", "southwest"}),
           "The rocks make it impossible to go that way.\n");
  
}
