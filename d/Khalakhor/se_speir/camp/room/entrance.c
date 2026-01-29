inherit "/std/room";
#include "/w/stark/defs.h"
void
create_room()
{
  ::create_room();
  set_short("a small clearing before a hidden Celtic Camp");
  set_long("You have made your way through the forest and mountain trail, and "
	  +"now have come across a suspicious-looking encampment. Hearing "
      +"the noise before your eyes could even register it. "
	  +"Even worse is the pungent odor that you can smell from here. Before you is "
      +"the gate to enter the clan's base of operations not far ahead to the north.\n");
  add_item(({"camp","encampment","base","base of operations"}),
      "Before you stands a hastily established encampment of celtic barbarians! "
	 +"Row after row of red and black striped tents create the campground, and "
     +"you begin to realize the true scope of military power that stands "
	 +"to threaten Port Macunn!\n");
  add_item(({"tent", "tents", "rows"}),
      "These rows of tents arrange a block format. each row holding five "
	 +"tents each, set up extremely well, even though it is evident that "
	 +"the tents have been set up very recently. Each tent holds a red "
     +"and black striped pattern, as they are the colours of the clan Baran! "
     +"Before the camp is an engraving in a very large tree.\n");
  add_item(({"engraving"}),
      "The engraving reads: Here is the current military camp "
     +"of the clan Baran.\n"); 
  add_item(({"forest","wild",}),
	  "The forest surrounds you to the north and south. Emitting "
	 +"natural sounds and a general relaxing atmosphere.\n");
  add_item(({"trail","rough trail","path"}),
	  "It's not much of a trail, but your keen eyes can see it " 
	 +"go from the east and lead to the west, towards what "
	 +"remains to be known.\n");
  add_item(({"wildlife","sounds"}),
	  "The forest seems to be surrounding you totally and utterly. "
	 +"Around you, are colourful birds on branches and squirrels "
	 +"darting through the underbrush.\n");
  add_item(({"wildlife","sounds"}),
		  "A quickly assembled gate stands before you to the north, "
		 +"if you go north, you could probably get a closer look.\n");
  add_exit(CAMP_DIR2+"camp1","north",0,0);
  add_exit(CAMP_DIR+"path14","south",0,0);
}
