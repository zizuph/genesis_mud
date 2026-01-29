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
  set_short("net2");
  
  set_long("net2.\n");

  add_exit(TOWERS + "net1", "west", 0, 0, 0);
  add_exit(TOWERS + "net3", "southwest", 0, 0, 0);
  add_exit(TOWERS + "net4", "south", 0, 0, 0);
  add_exit(TOWERS + "net6", "up", 0, 0, 0); 
  //add_exit(DUNGEON + "", "down", 0, 0, 0);
  reset_room();
}


