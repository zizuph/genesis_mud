/*
* Created by: See /d/Cirath/events/castledoom/code.txt
* Date: Dec 2001 
*
* Comments: Tower room
*/

#include "defs.h"

inherit CASTLEDOOM + "base_inside";

void
create_inside_room()
{
  set_short("NWT5");
  
  set_long("NTW5.\n");

  add_exit(TOWERS + "nwt1", "down", 0, 0, 0);
  add_exit(TOWERS + "nwt6", "east", 0, 0, 0);
  add_exit(TOWERS + "nwt7", "south", 0, 0, 0);
  add_exit(TOWERS + "nwt8", "southeast", 0, 0, 0);
  add_exit(TOWERS + "nwt9", "up", 0, 0, 0);
  reset_room();
}


