/*
* Created by: See /d/Cirath/events/castledoom/code.txt
* Date: Dec 2001 
*
* Comments: Tower room
*/

#include "defs.h"

inherit CASTLEDOOM + "base_inside";

void
create_inside_room()
{
  set_short("net1");
  
  set_long("net1.\n");

  add_exit(TOWERS + "net2", "east", 0, 0, 0);
  add_exit(TOWERS + "net3", "south", 0, 0, 0);
  add_exit(TOWERS + "net4", "southeast", 0, 0, 0);
  add_exit(HALL + "nh3", "west", 0, 0, 0); 
  reset_room();
}


