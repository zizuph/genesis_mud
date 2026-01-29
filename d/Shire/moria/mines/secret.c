#include "defs.h"

CONSTRUCT_ROOM
{
   set_short("Secret room");
   set_long(
      "You have found the Secret Room.\n"
      + "The room however seems very empty, and probably abandoned long "
      + "time ago. There are no exits but back north.\n");
   
   NORTH("bighallw");
   add_call("west", 0, "go_west");
}

int
go_west()
{
   TP->move_living("west", THIS_DIR + "mostsecr");
   return 1;
}
