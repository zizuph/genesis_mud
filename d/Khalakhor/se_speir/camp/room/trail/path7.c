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
	
    set_long("The trail now leads further into the mountain, forcing "
  	  +"you to travel upwards, or further out of the mountain, forcing "
  	  +"you to travel downwards. You gaze out into the distance at the "
  	  +"completely beautiful scene around you: the valley, the sky, and "
  	  +"wilderness itself around you creating an environment of general "
      +"peace. To the north, there is a slope for which must be climbed "
	  +"to go northwards.\n");
	
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
	
    add_item(({"slope","north","northwards"}),
	      "To the north, the trail goes up a natural slope. If "
	     +"you choose to ascend into the mountains of Khalakhor, "
	     +"you are quite aware that the air will get "
	     +"thinner and climbing will become more difficult.\n");
		  
  add_exit(CAMP_DIR+"path8","up",0,1);
  add_exit(CAMP_DIR+"path6","southwest",0,1);
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
	+"Here, only sounds of nature are present. From the wind "
	+"whistling through the trees or the animal calls in the "
    +"background, a gentle atmosphere is created by this "
	+"grouping of ambient noise.\n");
    return 1;
}

public void
init()
{
    ::init();
    add_action(listen_sounds, "listen");
}
