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
  set_short("cy4");
  
  set_long("cy4.\n");

  add_exit(COURT + "cy1", "north", 0, 0, 1);
  add_exit(COURT + "cy2", "northeast", 0, 0, 1);
  add_exit(COURT + "cy5", "east", 0, 0, 1);
  add_exit(COURT + "cy7", "south", 0, 0, 1);
  add_exit(COURT + "cy8", "southeast", 0, 0, 1);
  reset_room();
}


