#include "defs.h"

inherit M1_IN_BASE;

#include <stdproperties.h>

void
create_m1_room()
{
     add_exit("m1_42", "east");

     load_clone_handler = 1;

     add_prop(ROOM_M_NO_TELEPORT, 1);
}
 
