inherit "/std/room";

#include "/d/Roke/common/defs.h"

void
create_room()
{
   set_short("Secret passage");
   set_long("This is a secret tunnel underneath the gladiator "+
     "guild. The air is dry and foul smelling. It is very dark "+
     "farther down the tunnel, but it seems like it goes a "+
     "long way.\n");

   DARK

   add_exit(TYR+"stadium/p2","southeast",0,2);
   add_exit(GLAD_DIR+"joinroom","up");
}
