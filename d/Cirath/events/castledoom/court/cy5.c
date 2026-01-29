/*
* Created by: See /d/Cirath/events/castledoom/code.txt
* Date: Dec 2001 
*
* Comments: Courtyard
*/

#include "defs.h"

inherit CASTLEDOOM + "base_outside";

void
create_outside_room()
{
  set_short("cy5");
  
  set_long("cy5.\n");

  add_exit(COURT + "cy1", "northwest", 0, 0, 1);
  add_exit(COURT + "cy2", "north", 0, 0, 1);
  add_exit(COURT + "cy3", "northeast", 0, 0, 1);
  add_exit(COURT + "cy4", "west", 0, 0, 1);
  add_exit(COURT + "cy6", "east", 0, 0, 1);
  add_exit(COURT + "cy7", "southwest", 0, 0, 1);
  add_exit(COURT + "cy8", "south", 0, 0, 1);
  add_exit(COURT + "cy9", "southeast", 0, 0, 1);
  add_exit(COURT + "b1", "down", 0, 0, 1);
  reset_room();
}


