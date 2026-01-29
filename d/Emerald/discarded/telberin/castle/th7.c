/*
 * Th7.c
 * Castle Telberin
 * - Alaron January 1997
 */

#include "default.h"

inherit CASTLE_ROOM;

void
create_room()
{
    ::create_room();
    set_short("A small foyer");
    set_long("   You are in a small foyer. The room is square and "+
	     "totally undecorated. The walls are bare of paintings "+
	     "or any other decoration. A set of stairs leads up "+
	     "into the darkness in the south wall. The north wall "+
	     "is interrupted only by a plush red curtain which covers "+
	     "a narrow exit leading north. A somewhat cool draft "+
	     "blows gently down from the stairs above. It is "+
	     "a refreshing change from the heat which pours through "+
	     "the curtain to the north.\n\n");
    
    add_item("stairs",
	     "The stairs lead up through the south wall into darkness "+
	     "above.\n");

    add_item( ({"curtain", "red curtain", "plush red curtain",
		"plush curtain"}),
	     "The plush red curtain hangs loosely over the exit "+
	     "leading north. It is probably there to keep the draft "+
            "from blowing into the room beyond.\n");

   add_exit(CASTLE_DIR + "th5","north", "@@curtain");
   add_exit(CASTLE_DIR + "stairs","up", 0);
}

int
curtain()
{
    write("You step through the exit leading north, gently pushing "+
	  "the curtain aside ... \n\n");
    say(QCTNAME(TP)+" steps through the exit leading north, gently "+
	"pushing the curtain aside.\n");
    return 0;
}
