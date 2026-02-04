inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Terel/common/terel_defs.h"     
#include "tomb.h"

/* int ribbon_gone_flag; 

reset_room()
{
     ribbon_gone_flag = 0;
}

init()
{
     add_action("do_search", "search");
     ::init();
}

*/

create_room()
{
    set_short("cottage bedroom");
    set_long(
	"A small bedroom off of the kitchen.  The flagstone floor only " +
	"reaches part way into the room and the rest of the floor is " +
	"covered with shale tiles.  There is a small bed in along one wall.\n"
    );

    add_item(({"bed", "small bed"}), 
	"The small bed is on a wooden frame.  The headboard is inscribed " +
	"with the initials S.A.\n"
    );

    add_prop(ROOM_I_INSIDE, 1);

    add_exit(TOMBDIR + "cottage_kitchen", "west", 0);
    
}

/* 
do_search(string str)
{
     notify_fail("search what?\n");
     
     object ribbon;

     if (str == "here") {
	  if (!ribbon_gone_flag) {
	       ribbon_gone_flag = 1;
	       ribbon = clone_object(TOMBDIR + "ribbon");
	       ribbon->move(TO);
	       write("You find a metal ribbon.\n");
	       say(QCTNAME(TP) + " finds something that was hidden here.\n");
	  }
	  else
	       write("Your search reveals nothing special.\n");
	  
	  return 1;
     }

     return 0;
}
*/


