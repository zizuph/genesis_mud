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
  set_short("NWT9");
  
  set_long("NTW9.\n");

  add_exit(TOWERS + "nwt5", "down", 0, 0, 0);
  add_exit(TOWERS + "nwt10", "east", 0, 0, 0);
  add_exit(TOWERS + "nwt12", "southeast", 0, 0, 0);
  add_exit(TOWERS + "nwt11", "south", 0, 0, 0);
  add_exit(TOWERS + "nwt13", "up", 0, 0, 0);
  reset_room();
}


