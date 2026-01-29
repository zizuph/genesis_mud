/*
* Created by: Luther
* Date: Septt 2001
*
* File: /d/Cirath/ridge/valley/ruin_1.c
* Comments: The ruins inside the valley
*/

#pragma strict_types
#pragma save_binary

#include "defs.h"

inherit BASE_VALLEY;

void
create_valley()
{
  set_short("Ruins");
  set_long("You are standing in the middle of some ancient ruins. There or 3 buildings "
  	+"in these ruins and in the middle of the ruins is a fountain.\n");
  
  add_item("fountain", "In the middle of the ruins is a fountain. It looks like it "
  	+"hasn't been used in centuries. When you look in to it there doesn't "
  	+"appear to be any water.\n");
	
  add_item(({"building", "buildings"}), 
	"Looking at the buildings you see that they are in bad shape, sitting here "
	+"for hundreds of years. The grey building looks the worst with its roof "
	+"collapsed in. The brown building seems to be in better shape with its roof "
	+"still mostly intact. Its door appears to be missing aswell. In the "
	+"northeast corner of the ruins stands a beautiful building. It appears "
	+"to be untouched by time. It has green vines painted into the front of "
	+"it and has an amazing door. It looks like solid gold but when you take "
	+"a closer look its just the reflection of the sun on the polished door.\n");
	
  add_item("grey building", "Looking around the grey building you don't see much. "
  	+"Its imposible to get in there with the roof collapsed in. Looking under "
  	+"the back side of the building you can see some broken pots and furniture.\n");
  	
  add_item("brown building", "The brown building is missing the front doors. Looking "
  	+"in you can some old broken furniture. Otherwise the building appears to be "
  	+"fine. Most of the stone used to make this building appears to be intact.\n");
  	  	
  add_item("green building", "Amazed by the beauty of this building, it appears to be "
  	+"untouched by time. It has green vines painted into the front of it and the "
  	+"looks like solid gold. All the walls are solid and the roof is made of stone "
  	+"aswell. There is a huge window on the east side of the building.\n");
  
  add_item(({"pots", "furniture"}), "The furniture and pots have not been used "
  	+"in a long time. Most of them are broken and unusable. You do not find "
  	+"anything worth salvaging.\n");
  	
  add_item("green vines", "Green vines cover the front of the grey building. They "
  	+"look almost real, however plants don't grow in deserts. You notice 6 "
  	+"different patterns in total and they all point towards the door.\n");
  	
  add_item("door", "It looks like solid gold but when you take a closer look its "
  	+"just the reflection of the sun on the polished door. The door is closed.\n");	
  
  add_cmd_item("door", "open", "You try to open the stone door but it is locked!\n");
  
  add_cmd_item("furniture", "get", "None of the furniture is worth taken.\n");
  
  add_cmd_item("pots", "get", "None of the pots are worth taken.\n");
     	
  	add_exit(RIDGE_VALLEY+"v12.c","out",0,8,0);

	add_cmd_item("fountain", "enter", "@@fountain");
	add_cmd_item("window", "enter", "@@window");
 	add_cmd_item("building", "enter", "@@building");
}

int
fountain()
{   
        TP->catch_msg("You enter the fountain.\n");
        TP->move_living("climbing down the fountain", RIDGE_VALLEY + "v_fountain.c"); 
        return 1;     
}

int
window()
{   
	TP->catch_msg("You climb through the open window.\n");
        TP->move_living("climbing in the window", RIDGE_VALLEY + "v_ew.c");  
        return 1;     
}

int
building()
{   
	TP->catch_msg("You enter the grey building.\n");
        TP->move_living("entering the grey building", RIDGE_VALLEY + "v_gb.c");
        return 1;     
}