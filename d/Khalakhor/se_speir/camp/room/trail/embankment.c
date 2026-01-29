inherit "/std/room";
#include "/w/stark/defs.h"

void
create_room()
{
  ::create_room();
  set_short("On the top of the embankment");
  set_long("You are standing ontop of the western defensive embankment "
	     +"of the city of Port Macdunn. This defensive wall seperates "
	     +"the tranquil wild to your east and the defeaning sound of "
	     +"the working port to your east. The wind is harsh and  "
	     +"unrelenting, pushing you to the west, making it hard to  "
         +"stand here for a long period of time.\n");
  
  add_item(({"wilderness","forest","wild","tranquil wild"}),
          "Before you, to the west of this great embankment is a "
		 +"large forest, full of wildlife and vegetation. This is "
		 +"a stark contrast to the relatively close port. To your "
		 +"west you see a path which offers respite against the "
		 +"chilling wind here.\n");
		  
  add_item(({"wind", "biting wind","harsh wind",}),
	      "A fierce, biting wind is constantly pushing you to the west, "
		 +"making it quite difficult to stand still upon the "
		 +"top of the embankment.\n");
		  
  add_item(({"embankment","wall","western defensive embankment"}),
		  "You stand ontop of the earthen embankment which serves as "
	     +"a defensive wall around the village to protect against "
	     +"invasion. Sadly, it isn't much to look at, little "
	     +"more than hard-packed soil heaped at about a forty-five "
	     +"degree slope.\n");
		  
  add_item(({"port macdunn","town","civilized town"}),
		  "The town is to your direct east, the sounds still "
	     +"within earshot. You can make out the different " 
		 +"villagers as you gaze over the town. The inhabitants "
		 +"inhabitants going about their regular business.\n");	
				  		    
  add_exit("/d/Khalakhor/se_speir/port/room/road_3_7","down",0,0);
  add_exit(CAMP_DIR+"path1","west",0,0);
  
}
