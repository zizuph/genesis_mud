inherit "/std/room";

#include "default.h"
#include <stdproperties.h>

void
create_room()
{
   set_short("Bedroom");
   set_long("This bedroom looks to be the siblings of the Lord's, messy and " +
            "full of junk, weapons with which to while away a youngsters " +
            "life. The bed is a mess, not even tidied.\n");
   
   add_prop(ROOM_I_INSIDE, 1);
   
   add_exit(THIS_DIR + "up1", "southeast");
   
   add_item("junk","The average youngsters junk, things to use and play "+
	"with.\n");
   add_item("bed","The bed is a mess, just slept in, and not very tidy.\n");
}
