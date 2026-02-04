inherit "/std/room";
     
#include <stdproperties.h>
#include <macros.h>

#include "/d/Terel/common/terel_defs.h"
#include "tomb.h"

init()
{
     add_action("do_dive", "dive");
     add_action("do_dive", "enter");     
     ::init();
     
}

do_dive(string str)
{
    object sorgum;


     if ((str == "grime") || (str == "in")) {      
      write("You dive down through the murky grime.  You are lucky this " +
          "time.  You managed to find your way through it.  Next time " +
          "you come here it might not be so easy!\n");
      TP->move_living("into the grimy sludge", TOMBDIR + "gore_chamber");


      /*
       * Tell me when players enter Benton's room.
       */
      
     sorgum = find_player("sorgum");
     if (sorgum)
	 sorgum->catch_msg(TP->query_real_name() + " went into " +
			   "the gore chamber.\n");
      
      return 1;
 }

	  notify_fail("Sorry, try a different syntax\n");
	  return 0;     
}
     
void
create_room()
{
    set_short("Grime river");
    set_long(
	"You are following a slimy expanse of hellish black mire " +
	"which extends in monotonous undulations as far as you can see.  " +
	"In the air is a sinister quality that chills you to the core.  " +
	"This region is putrid with carcasses of dying fish and " +
	"other less desirable things which you see protruding from the " +
	"nasty grime.\n"
    );

    
    add_item(({"fish", "carcass", "carcasses"}),
        "The carcasess reek of decay.  Various tentacles and fins of " +
        "strange fish and other water creatures look gruesome.\n"
        );

    add_item(({"grime", "mire"}), 
	"It looks just awful.  You don't dare try and enter it or " +
        "dive in, or something terrible might happen to you.\n"
    );
    
    add_prop(ROOM_I_INSIDE, 1);

    add_exit(TOMBDIR + "tomb_core", "south", 0);
}
