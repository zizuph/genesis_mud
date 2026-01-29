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
  
  set_long("You stand on a faded trail, leading to the east and west. The path lies "
	  +"east of Port Macdunn, yet the landscape looks completely different to "
	  +"that of Port Macdunn's. The forest is alive with wildlife, and you hear "
	  +"only the sounds of nature and the environment around you. A very soothing "
	  +"atmosphere overtakes you as Port Macdunn fades to the background. Overhead, "
	  +"the sky is light blue, spotted with idle clouds floating by. The path "
	  +"continues to the west and east.\n");
  
  add_item(({"port macdunn"}),
      "The town is barely heard from this point, " 
     +"while you are able to see the tops of buildings, "
	 +"the commotion that was so common there has "
	 +"disappeared on this gentle path.\n");
	  
  add_exit(CAMP_DIR+"path2","east",0,1);
  add_exit(CAMP_DIR+"path4","west",0,1);
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
	+"The noise of the active port to the east is not as prevalent "
	+"here, the air taken over by the sounds of wildlife as the "
    +"forest continues to teem with activity. You hear the birds "
	+"and squirrels, darting in between branches and underbrush, "
	+"respectively.\n");
    return 1;
}

public void
init()
{
    ::init();
    add_action(listen_sounds, "listen");
}