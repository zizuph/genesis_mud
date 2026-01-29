inherit "/std/room.c";
#include "/sys/stdproperties.h"
#include "defs.h"

void
create_room()
{
   set_short("short");
   set_long("long\n");
   add_exit(THIS_DIR + "where", "dir");
   add_prop( ROOM_I_INSIDE, 1 );
}
