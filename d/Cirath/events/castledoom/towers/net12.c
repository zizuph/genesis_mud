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
  set_short("net12");
  
  set_long("net12.\n");

  add_exit(TOWERS + "net9", "northwest", 0, 0, 0);
  add_exit(TOWERS + "net10", "north", 0, 0, 0);
  add_exit(TOWERS + "net11", "west", 0, 0, 0);
  add_exit(HALL + "eh4", "south", 0, 0, 0);
  reset_room();
}


