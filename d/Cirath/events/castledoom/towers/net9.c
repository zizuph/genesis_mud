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
  set_short("net9");
  
  set_long("net9.\n");

  add_exit(TOWERS + "net10", "east", 0, 0, 0);
  add_exit(TOWERS + "net12", "southeast", 0, 0, 0);
  add_exit(TOWERS + "net11", "south", 0, 0, 0);
  add_exit(HALL + "nh6", "west", 0, 0, 0);
  reset_room();
}


