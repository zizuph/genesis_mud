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
  set_short("net10");
  
  set_long("net10.\n");

  add_exit(TOWERS + "net6", "down", 0, 0, 0);
  add_exit(TOWERS + "net9", "west", 0, 0, 0);
  add_exit(TOWERS + "net11", "southwest", 0, 0, 0);
  add_exit(TOWERS + "net12", "south", 0, 0, 0);
  add_exit(TOWERS + "net14", "up", 0, 0, 0);
  reset_room();
}


