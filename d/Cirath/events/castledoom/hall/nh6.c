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
  set_short("nh6");
  
  set_long("nh6.\n");

  add_exit(HALL + "nh5", "west", 0, 0, 0);
  add_exit(TOWERS + "net9", "east", 0, 0, 0);
  reset_room();
}


