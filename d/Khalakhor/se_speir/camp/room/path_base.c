inherit "/std/room";
#include "/w/stark/defs.h"
void
create_room()
{
  ::create_room();
	 
	  
  add_item(({"trail","rough trail","path"}),
      "It is merely a worn, simple "
     +"dirt path, nothing much to note.\n");
	   
  add_item(({"forest","wild","landscape", "atmosphere","scene","wilderness"}),
      "The forest surrounds you completely. To the north, "
     +"you can make out the peaks of great mountains. To "
     +"the west, you can see countless trees, fading into "
     +"the distance, around you the forest seems to be alive: "
	 +"emitting natural sounds and a general relaxing atmosphere.\n");
	  
  add_item(({"wildlife","sounds"}),
	  "The forest seems to be surrounding you totally and utterly. "
     +"Around you, are colourful birds on branches and squirrels "
	 +"darting through the underbrush. If you try hard enough, you "
	 +"seem to be able to listen to the sounds of the wild around you.\n");
	  
  add_item(({"squirrels","birds",}),
      "Wildlife in the forest make the landscape around you alive. "
     +"Bushy squirrels dart through the grass and birds fly quickly "
	 +"between the trees above you. You are surrounded by ambient "
	 +"noise of life.\n");

  add_item(({"sky","clouds"}),
	  "Looking upwards, the sky appears to be as calming as the forest "
	 +"around you currently. As time passes, Idle clouds float by.\n"); 
	   
	   
}

