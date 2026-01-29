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
  set_short("nh5");
  
  set_long("nh5.\n");

  add_exit(HALL + "nh4", "west", 0, 0, 0);
  add_exit(HALL + "nh6", "east", 0, 0, 0);
  reset_room();
}


