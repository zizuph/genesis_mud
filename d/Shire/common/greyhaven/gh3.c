inherit "/std/room";

#include "defs.h"

create_room() {


   set_short("The Great Eastroad");
   set_long("@@long_desc");

   add_item(({ "track", "tracks" }), "The tracks are mostly made by wagons "
	    + "and mules. There are also a few that indicate horses.\n");

   add_item(({"towers", "white towers", "White Towers"}), "They look "
	    + "like they are closed to the public.\n");


   add_exit(STAND_DIR + "gh2", "east", 0);
   add_exit(STAND_DIR + "gh6", "west", 0);
}

string long_desc() {

  string str;

  str = "You are travelling on the Great Eastroad. To the west you can "
    + "see the White Towers.\n";
	
  return break_string(str,77);

}



