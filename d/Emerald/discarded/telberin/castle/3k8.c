#include "default.h"

inherit CASTLE_ROOM;

void
create_room()
{
   set_short("Tower");
   set_long("You have found the northwestern tower. The exits are up "+
            "and southeast.  It is very damp and dry in here.\n");   

   add_exit(CASTLE_DIR + "3k1","southeast");

}
