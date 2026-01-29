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
  set_short("cy3");
  
  set_long("cy3.\n");

  add_exit(TOWERS + "net3", "northeast", 0, 0, 0);
  add_exit(COURT + "cy2", "west", 0, 0, 1);
  add_exit(COURT + "cy5", "southwest", 0, 0, 1);
  add_exit(COURT + "cy6", "south", 0, 0, 1);
  reset_room();
}


