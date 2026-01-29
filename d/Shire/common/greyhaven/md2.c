inherit "/d/Shire/room";
#include "/d/Shire/common/defs.h"

#include "defs.h"
#include "/sys/macros.h"

create_room() {


   set_short("The Great Eastroad");
   set_long("You are in the small village Michel Delving. "+
   "To the east and west are houses that look like guardrooms, "+
   "and to the south a residence has opened its doors. "+
   "North you will find the Eastroad.\n");

   add_item(({ "track", "tracks" }), "The tracks are mostly made by wagons "
	    + "and mules. There are also a few that indicate horses.\n");

   add_item(({ "door", "doors" }), "There is nothing unusual about these "
	    + "wooden doors except for their round shape.\n");

    add_exit(MICH_DIR + "grdroom", "west",0,1);
    add_exit(MICH_DIR + "grdroom2","east",0,1);
   add_exit(GHAVEN_DIR + "gh1","north",0,1);
   add_exit(MICH_DIR + "task", "south",0,1);
  
}


string size() {

  if (this_player()->query_race() != "hobbit") {
    write("You have problems getting in through the small door.\n");
  }

  return 0;
}
  
