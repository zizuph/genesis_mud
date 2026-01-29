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
  set_short("sh3");
  
  set_long("sh3.\n");

  add_exit(HALL + "sh2", "west", 0, 0, 0);
  add_exit(TOWERS + "set11", "east", 0, 0, 0);
  reset_room();
}


