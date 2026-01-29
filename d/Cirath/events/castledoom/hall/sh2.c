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
  set_short("sh2");
  
  set_long("sh2.\n");

  add_exit(HALL + "sh1", "west", 0, 0, 0);
  add_exit(HALL + "sh3", "east", 0, 0, 0);
  reset_room();
}


