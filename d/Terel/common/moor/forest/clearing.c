/*
    Modified: 6 May 2003, by Bleys
        - added a missing newline in the briars desc

*/
// updated by Lilith Dec 2021: moved from Sorgum's dir to Terel/common
//    updated to Terel std room, etc

inherit "/std/room";

#include "/d/Terel/include/Terel.h"
inherit STDROOM;
#include "../local.h"

void
init()
{
     ::init();
     add_action("do_enter", "enter");
     add_action("do_push", "push");
}

void
create_room()
{
    set_short("small clearing");
    set_long("You have stepped into a small clearing before the mold-"+
	     "stained facade of a hillside.  Surrounding vegetation "+
	     "encircles and overhangs the space of the clearing like "+
	     "the walls and roof of a sylvan bower. In front of the "+
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

    add_exit("forest01", "southeast", 0);
}


int
try_enter()
{
     
     say(QCTNAME(TP) + " scrapes through the briars.\n");
     TP->move_living("through briars", MOOR_DIR + "tomb/tomb_ent", 1);
     return 1;
}

int
do_enter(string str)
{
     notify_fail("Enter what?\n");
     if ((str == "briars") || (str == "briar")) {
	  try_enter();
	  return 1;
     }
     return 0;
}

int
do_push(string str)
{
     notify_fail("Push past what?\n");
     if ((str == "past briars") || (str == "past briar")) {
	  try_enter();
	  return 1;
     }
     return 0;
}
