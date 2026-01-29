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
  set_short("cy6");
  
  set_long("cy6.\n");

  add_exit(COURT + "cy2", "northwest", 0, 0, 1);
  add_exit(COURT + "cy3", "north", 0, 0, 1);
  add_exit(COURT + "cy5", "west", 0, 0, 1);
  add_exit(COURT + "cy8", "southwest", 0, 0, 1);
  add_exit(COURT + "cy9", "south", 0, 0, 1);
  reset_room();
}


