#include "../local.h"

inherit FOREST_BASE;

void
create_forest_room()
{
   set_short("In a gloomy forest near a road");
   set_long("The forest is filled with shadows and strange "+
	    "noises.  The light of day barely penetraits the "+
	    "dense leaves of the forest trees.  The light is the "+
	    "strongest towards the east and a there seems to be a faint path "+
	    "here leading in a northwestern direction.\n");

   add_item("shadows","They seem to linger everywhere.\n");
   add_item("light","It is very faint, filtering in from the east "+
	    "when you believe the road might be.\n");
   add_item("path","A lightly travelled path leading you further into "+
	    "this forest.\n");

   set_room_tell_time(45);//Players will recieve a room tell every 45 seconds

   /* The list of tells yhe player could recieve */
   add_room_tell("You hear the leaves rustle in the wind.");
   add_room_tell("A wolf's howl in the distance startles you.");
   add_room_tell("In the distance you hear the song of a bird chriping.");
   add_room_tell("The smell of wild flowers tickles your nose.");
   add_room_tell("Faint noises echo from the northwest.");

   add_exit(EXAMPLE_ROAD + "road3","east",0,3);
   add_exit(EXAMPLE_FOREST + "forest2","northwest",0,4);
}

