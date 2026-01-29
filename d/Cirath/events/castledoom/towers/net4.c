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
  set_short("net4");
  
  set_long("net4.\n");

  add_exit(TOWERS + "net1", "northwest", 0, 0, 0);
  add_exit(TOWERS + "net2", "north", 0, 0, 0);
  add_exit(TOWERS + "net3", "west", 0, 0, 0);
  add_exit(HALL + "eh1", "south", 0, 0, 0);
  reset_room();
}


