inherit "/std/room";

#include "/d/Roke/common/defs.h"

void
create_room()
{
   set_short("Long, dark tunnel");
   set_long("This is an extremely long tunnel, carved out "+
     "the rock and earth. The air is dry and foul.\n");

   DARK

   add_exit(TYR+"stadium/p1","northwest",0,2);
   add_exit(TYR+"stadium/p3","east",-23,4);
}
