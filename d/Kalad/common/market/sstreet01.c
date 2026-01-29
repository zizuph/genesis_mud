inherit "/std/room";

#include "/d/Kalad/defs.h"

void
create_room()
{
   set_short("Serpent Street");
   set_long("On Serpent Street.\n");
   
   add_exit(MRKT_PATH(m17), "east");
}
