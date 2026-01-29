inherit "/std/room";
inherit "/w/stark/celtcamp/rooms/path_base";
#include "/w/stark/defs.h"
#include <ss_types.h>
#include <macros.h>

string listen_sounds(string str);

void
create_room()
{
    ::create_room();
	set_short("On a worn trail");
	
    set_long("The trail now leads further into the mountains to the "
  	    +"general northwest, as you move onwards, you glance at "
        +"the tranquil beauty that the forest has created around you. "
        +"Presently, you are at the top of the slopes that lead to the "
        +"top of this mountain. You are surrounded by clouds, and below  "
        +"you can see Port Macdunn in the distance, and an "
	    +"overlook of the valley.\n");
	
    add_item(({"Port Macdunn"}),
		 "In this distance you see a faint outline of Port Macdunn.\n");
   
    add_item(({"mountain", "mountain range", "mountains"}),
		 "Around you are the great mountain range of Khalakhor, as you "
		+"gaze around you, you realize how numerous the mountains are. "
	    +"The range goes on, deep into the distance, casting great "
	    +"shadows into the valley below.\n");
		 
    add_item(({"shadow", "shadows", "valley"}),
	     "To the east of the great mountain range, a large grouping "
	    +"of shadows lay upon the valley below. From this vantage "
	    +"point, Port Macdunn seems like a very small city in "
	    +"comparason to the size of the wild that surrounds it.\n");
		 
    add_item(({"port macdunn"}),
	  	 "The town is hard to see through the thick trees around "
	   	+"you, perhaps closer to the top of this mountain, you will "
	   	+"be able to get a better vantage point.\n");
		
    add_item(({"peak","summit","outlook"}),
	     "To the north, you can see the top of the mountain you "
	    +"have been hiking up. Perhaps there, you will be able to "
	    +"gather a full picture of the valley below.\n");
		
		
	add_exit(CAMP_DIR+"path12","northwest",0,1);
	add_exit(CAMP_DIR+"path10","east",0,1);
  
}

int
listen_sounds(string str)
{
    
    notify_fail("listen to what?\n");
    if (str != "to sounds" && str != "to the sounds" 
    && str != "the atmosphere" && str != "the environment"
    && str != "the environment" && str != "to the area"
    && str != "to the birds" && str != "to the animals"
    && str != "to the environment")
    return 0;
	
	   
    else
    say(QCTNAME(this_player()) +
    " gestures to stand still for a moment, taking a small second "
   +"to listen to the sounds around the area.\n");
	
    write("You take a moment to listen to the sounds around you. "
	+"Here the trees sway back and forth ominously, and there "
	+"are not as many animal calls heard. To the northwest, you "
    +"think you recognize the faint sound of sparring, blending "
	+"into the ambient noise.\n");
    return 1;
}

public void
init()
{
    ::init();
    add_action(listen_sounds, "listen");
}
