inherit "/std/room";

#include "default.h"

void
create_room()
{
   object drawbridge;
   
   set_short("Outside castle");
   set_long( "You are standing by a moat completely "+
      "surrounding an old castle. Just across the moat, you "+
      "are able to make out the entrance.\n" );
   
   add_item("castle", "This is an old castle. It's surrounded "+
      "by a deep moat.\n");
   add_item("moat", "The moat looks deep, and "+
      "the water looks muddy, and doesn't smell very nice "+
      "either.\n");
   
   add_exit(TOWNSHIP_DIR + "mainstreet3", "north");
   add_exit(TCASTLE_DIR + "by_moat", "west");
   
   drawbridge=clone_object(TCASTLE_DIR + "doors/drawbridge_b");
   drawbridge->move(this_object());
}
