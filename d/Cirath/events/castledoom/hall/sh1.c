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
  set_short("sh1");
  
  set_long("sh1.\n");

  add_exit(TOWERS + "swt12", "west", 0, 0, 0);
  add_exit(HALL + "sh2", "east", 0, 0, 0);
  reset_room();
}


