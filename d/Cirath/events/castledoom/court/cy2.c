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
  set_short("cy2");
  
  set_long("cy2.\n");

  add_exit(COURT + "cy1", "west", 0, 0, 1);
  add_exit(COURT + "cy3", "east", 0, 0, 1);
  add_exit(COURT + "cy4", "southwest", 0, 0, 1);
  add_exit(COURT + "cy5", "south", 0, 0, 1);
  add_exit(COURT + "cy6", "southeast", 0, 0, 1);
  reset_room();
}


