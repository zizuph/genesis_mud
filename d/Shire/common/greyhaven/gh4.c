inherit "/std/room";

#include "/d/Shire/common/defs.h"

create_room() {

   set_short("The Great Eastroad");
   set_long("@@long_desc");

   add_item(({ "track", "tracks" }), "The tracks are mostly made by wagons "
	    + "and mules. There are also a few that indicate horses.\n");

   add_item(({"towers", "white towers", "White towers"}), "They look "
	    + "like they are closed to the public.\n");



   add_exit(GHAVEN_DIR + "gh3", "east", 0);
   add_exit(GHAVEN_DIR + "gh5", "west", 0, 2);

}

string long_desc() {

  string str;

  str = "You are travelling on the Great Eastroad. To the west the "
    + "landscape is getting rougher as the road enters the hills. You are "
      + "passing just north of the White towers.\n";
	
  return break_string(str,77);

}



