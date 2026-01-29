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
  set_short("cy7");
  
  set_long("cy7.\n");

  add_exit(TOWERS + "swt2", "southwest", 0, 0, 0);
  add_exit(COURT + "cy4", "north", 0, 0, 1);
  add_exit(COURT + "cy5", "northeast", 0, 0, 1);
  add_exit(COURT + "cy8", "east", 0, 0, 1);
  reset_room();
}


