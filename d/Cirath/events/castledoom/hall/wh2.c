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
  set_short("wh2");
  
  set_long("wh2.\n");

  add_exit(HALL + "wh1", "north", 0, 0, 0);
  add_exit(HALL + "wh3", "south", 0, 0, 0);
  add_exit(SPECIAL + "sr1", "east", "@@special_enter", 0, 0);
  reset_room();
}

int
special_enter()
{
     if (!this_player()->query_wiz_level())
    {
    	write("You do not qualify to enter here yet.\n");
        return 1; // When player has X kills they can enter. Not yet coded.
    }
    
}
