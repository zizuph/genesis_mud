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
  set_short("net16");
  
  set_long("net16.\n");

  add_exit(TOWERS + "net13", "northwest", 0, 0, 0);
  add_exit(TOWERS + "net14", "north", 0, 0, 0);
  add_exit(TOWERS + "net15", "west", 0, 0, 0);
  reset_room();
}


