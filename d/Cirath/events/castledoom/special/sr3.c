/*
* Created by: See /d/Cirath/events/castledoom/code.txt
* Date: Dec 2001 
*
* Comments: Special rooms
*/

#include "defs.h"

inherit CASTLEDOOM + "base_inside";

void
create_inside_room()
{
  set_short("sr3");
  
  set_long("sr3.\n");

  add_exit(HALL + "eh2", "east", 0, 0, 0);
  reset_room();
}


