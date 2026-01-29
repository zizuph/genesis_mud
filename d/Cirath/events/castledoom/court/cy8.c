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
  set_short("cy8");
  
  set_long("cy8.\n");

  add_exit(COURT + "cy4", "northwest", 0, 0, 1);
  add_exit(COURT + "cy5", "north", 0, 0, 1);
  add_exit(COURT + "cy6", "northeast", 0, 0, 1);
  add_exit(COURT + "cy7", "west", 0, 0, 1);
  add_exit(COURT + "cy9", "east", 0, 0, 1);
  add_exit(GATE + "sg1", "south", 0, 0, 1);
  reset_room();
}


