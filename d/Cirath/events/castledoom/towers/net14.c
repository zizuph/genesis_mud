/*
* Created by: See /d/Cirath/events/castledoom/code.txt
* Date: Dec 2001 
*
* Comments: Tower room
*/

#include "defs.h"

inherit CASTLEDOOM + "base_outside";

void
create_outside_room()
{
  set_short("net14");
  
  set_long("net14.\n");

  add_exit(TOWERS + "net10", "down", 0, 0, 0);
  add_exit(TOWERS + "net13", "west", 0, 0, 0);
  add_exit(TOWERS + "net15", "southwest", 0, 0, 0);
  add_exit(TOWERS + "net16", "south", 0, 0, 0);
  reset_room();
}


