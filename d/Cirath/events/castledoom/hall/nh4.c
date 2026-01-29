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
  set_short("nh4");
  
  set_long("nh4.\n");

  add_exit(TOWERS + "nwt10", "west", 0, 0, 0);
  add_exit(HALL + "nh5", "east", 0, 0, 0);
  reset_room();
}


