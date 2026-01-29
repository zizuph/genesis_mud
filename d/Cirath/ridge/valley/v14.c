/*
* Created by: Luther
* Date: 19 August 2001
*
* File: /d/Cirath/ridge/valley/v14.c
* Comments: Valley outside of Tyr
*/

#pragma strict_types
#pragma save_binary
#include "defs.h"
inherit BASE_VALLEY;

void
create_valley()
{
  set_short("Sand Valley");
  set_long("You are standing on the western ridge of the valley. To the southwest, "
  	+"lies the end of the valley. Looking straight across the valley you see "
  	+"the other side. Taken a closer look you can see something moving over there.\n");

  add_item("end", "Looking southwards you see the end of the valley.\n");
	
  add_item(({"other", "something", "moving", "across", "over", "there"}), 
	"Looking to the other side of the valley you can make out "
	+"something shimmering around, almost like a ghost.\n");	

  add_exit(RIDGE_VALLEY+"v11.c","northeast",0,8,0);
  add_exit(RIDGE_VALLEY+"v15.c","east",0,8,0);
  add_exit(RIDGE_VALLEY+"v18.c","south",0,8,0);
  add_exit(RIDGE_VALLEY+"v17.c","southwest",0,8,0);
  reset_room();
}


