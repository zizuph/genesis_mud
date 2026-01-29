inherit "/std/room";

#include "defs.h"

create_room() {


   set_short("The Great Eastroad");
   set_long("@@long_desc");

   add_item(({ "track", "tracks" }), "The tracks are mostly made by wagons "
	    + "and mules. There are also a few that indicate horses.\n");

   add_item(({ "door", "doors" }), "There is nothing unusual about these "
	    + "wooden doors except for their round shape.\n");


   add_exit(STAND_PARENT + "hobbiton/er25", "east", 0);
   add_exit(STAND_DIR + "gh2", "west", 0);
   add_exit(STAND_DIR + "md1", "north", 0);
   add_exit(STAND_DIR + "md2", "south", 0);
  
}

string long_desc() {

  string str;

  str = "You are in the small village Michel Delving. The Great Eastroad "
        + "which you are standing on splits this village in two. The "
	  + "homes on either side of the road are all in the traditional "
	    + "hobbit design. They are all holes in the ground. Small "
	      + "round doors indicate where the entrances to them can "
		+ "be found.\n";
	
  return break_string(str,77);

}



