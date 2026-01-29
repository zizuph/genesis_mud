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
    set_short("At the Overlook");
	
    set_long("This is where the path north ends. To the southeast, "
		+"you can hear the sound of distant sparring, but to the "
  	    +"east, you are given a great glance at the tranquil beauty"
        +"created by the forest around you and the valley below. "
        +"Presently, you are at the top of mountain and have a great "
        +"vantage point to see Port Macdunn in the distance. The sun "
        +"is warm on your body, the wind cold on your skin, and "
	    +"you can see clouds below you.\n");
	
    add_item(({"peak","summit","outlook"}),
	     "To the north, you can see the top of the mountain you "
	    +"have been hiking up. Perhaps there, you will be able to "
	    +"gather a full picture of the valley below.\n");
		 
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
	    		 
		 
			
    add_exit(CAMP_DIR+"path12","southeast",0,1);
	add_exit(CAMP_DIR3+"training0","southwest",0,1);
  
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
	+"are not as many animal calls heard. to the northwest, the "
    +"sound of sparring is almost overbearing, overcoming "
	+"the relaxing, ambient noise of the forest.\n");
    return 1;
}

public void
init()
{
    ::init();
    add_action(listen_sounds, "listen");
}
