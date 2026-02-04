/*
    Modified: 6 May 2003, by Bleys
        - added a missing newline in the briars desc

*/

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Terel/common/terel_defs.h"     
#include "tomb.h"

init()
{
     ::init();
     add_action("do_enter", "enter");
     add_action("do_push", "push");
}

create_room()
{
    set_short("small clearing");
    set_long("You have stepped into a small clearing before the mold "+
	     "stained facade of a hillside.  Surrounding vegetation "+
	     "encircles and overhangs the space of the clearing like "+
	     "the walls and roof of a sylvan bower.  In front of the "+
	     "hillside is an enormous clump of savage briars.\n"
    );

    add_item(({"briars", "clumps"}), 
        "The briars are rather thick and are covered with large sharp " +
	"looking barbs.  They are obscuring what appears to be a strange " +
	"stone house set into a woodland slope.  You think you might be " +
	"able to push your way past, although you may get pricked by the " +
        "barbs in the process.\n"
    );

    add_prop(ROOM_I_INSIDE, 0);

    add_exit(TOMBDIR + "forest01", "southeast", 0);
}


do_enter(string str)
{
     notify_fail("Enter what?\n");
     if ((str == "briars") || (str == "briar")) {
	  try_enter();
	  return 1;
     }
     return 0;
}

do_push(string str)
{
     notify_fail("Push past what?\n");
     if ((str == "past briars") || (str == "past briar")) {
	  try_enter();
	  return 1;
     }
     return 0;
}

try_enter()
{
     /*
      * For now this is 1/16 of total hp... Maybe this should be some
      * absolute number instead.
      */
     
     say(QCTNAME(TP) + " scrapes through the briars.\n");
     TP->move_living("through briars", TOMBDIR + "tomb_ent", 1);
     return 1;
}


