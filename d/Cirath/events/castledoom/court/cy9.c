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
  set_short("cy9");
  
  set_long("cy9.\n");

  add_exit(TOWERS + "set1", "southeast", 0, 0, 0);
  add_exit(COURT + "cy5", "northwest", 0, 0, 1);
  add_exit(COURT + "cy6", "north", 0, 0, 1);
  add_exit(COURT + "cy8", "west", 0, 0, 1);
  reset_room();
}


