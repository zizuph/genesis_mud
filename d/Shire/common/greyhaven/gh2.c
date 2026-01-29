inherit "/std/room";

#include "defs.h"

create_room() {


   set_short("The Great Eastroad");
   set_long("@@long_desc");

   add_item(({ "track", "tracks" }), "The tracks are mostly made by wagons "
	    + "and mules. There are also a few that indicate horses.\n");

   add_item("village", "It is too far away for you to see anything special.\n");


   add_exit(STAND_DIR + "gh1", "east", 0);
   add_exit(STAND_DIR + "gh3", "west", 0);

  
}

string long_desc() {

  string str;

  str = "You are travelling on the Great Eastroad. To your east you can "
    + "see a small village. West of here the road continues to Grey Haven.\n";
	
  return break_string(str,77);

}



