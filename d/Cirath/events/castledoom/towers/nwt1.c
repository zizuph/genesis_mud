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
  set_short("NWT1");
  
  set_long("NTW1.\n");

  add_exit(TOWERS + "nwt2", "east", 0, 0, 0);
  add_exit(TOWERS + "nwt4", "southeast", 0, 0, 0);
  add_exit(TOWERS + "nwt3", "south", 0, 0, 0);
  add_exit(TOWERS + "nwt5", "up", 0, 0, 0);
  //add_exit(DUNGEON + "", "down", 0, 0, 0);
  reset_room();
}


