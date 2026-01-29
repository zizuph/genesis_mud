/*
* Created by: Luther
* Date: 19 August 2001
*
* File: /d/Cirath/ridge/valley/v08.c
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
  set_long("You are standing on the western ridge of the valley. Looking down "
  	+"below you see some ruins in the middle of the valley. To the northeast "
  	+"you see the entrance to the valley and to the southwest, the end of the "
  	+"valley. Looking straight across the valley you see the other side. "
  	+"Taken a closer look you can see something moving over there.\n");

  add_item("ruins", "Down in the middle of the valley you see old ruins of a "
	+"building long abandoned. "
	+"\n");

  add_item("entrance", "Looking northwards you see the beginning of the valley.\n");
	
  add_item("end", "Looking southwards you see the end of the valley.\n");
	
  add_item(({"other", "something", "moving", "across", "over", "there"}), 
	"Looking to the other side of the valley you can make out "
	+"something shimmering around, almost like a ghost.\n");
	
  add_exit(RIDGE_VALLEY+"v05.c","northeast",0,8,0);
  add_exit(RIDGE_VALLEY+"v09.c","east",0,8,0);
  add_exit(RIDGE_VALLEY+"v12.c","south",0,8,0);
  add_exit(RIDGE_VALLEY+"v11.c","southwest",0,8,0);
  reset_room();
}


