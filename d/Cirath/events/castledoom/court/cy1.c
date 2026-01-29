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
  set_short("cy1");
  
  set_long("cy1.\n");

  add_exit(TOWERS + "nwt4", "northwest", 0, 0, 0);
  add_exit(COURT + "cy2", "east", 0, 0, 1);
  add_exit(COURT + "cy4", "south", 0, 0, 1);
  add_exit(COURT + "cy5", "southeast", 0, 0, 1);
  reset_room();
}


