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
  set_short("wh4");
  
  set_long("wh4.\n");

  add_exit(TOWERS + "nwt11", "north", 0, 0, 0);
  add_exit(HALL + "wh5", "south", 0, 0, 0);
  reset_room();
}


