inherit "/std/room";

#include "/d/Roke/common/defs.h"

void
create_room()
{
   set_short("End of secret tunnel");
   set_long("This is the end of the secret passageway. "+
     "It is quite dark and dry here. To the west is "+
     "the way back. Up is a trap door that leads to an "+
     "unknown place.\n");

     DARK

  add_exit(TYR+"stadium/stadium","up",0,2);
   add_exit(TYR+"stadium/p2.c","west",-23,4);
}
