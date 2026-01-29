/*
* Created by: See /d/Cirath/events/castledoom/code.txt
* Date: Dec 2001 
*
* Comments: Hall room
*/

#include "defs.h"

inherit CASTLEDOOM + "base_inside";

void
create_inside_room()
{
  set_short("nh3");
  
  set_long("nh3.\n");

  add_exit(HALL + "nh2", "west", 0, 0, 0);
  add_exit(TOWERS + "net1", "east", 0, 0, 0);
  reset_room();
}


