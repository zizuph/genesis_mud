/*
* Created by: See /d/Cirath/events/castledoom/code.txt
* Date: Dec 2001 
*
* Comments: Hall room
*/

#include "defs.h"

inherit CASTLEDOOM + "base_outside";

void
create_outside_room()
{
  set_short("eh4");
  
  set_long("eh4.\n");

  add_exit(TOWERS + "net12", "north", 0, 0, 0);
  add_exit(HALL + "eh5", "south", 0, 0, 0);
  reset_room();
}


