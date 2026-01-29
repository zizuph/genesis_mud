inherit "/d/Gondor/common/lib/town";

#include "/d/Gondor/defs.h"

void   reset_room();

void
create_room() 
{
   hillside="north";
   height=2;
   road=4;
   density=3;
   extraline = "Here Kingsroad and the staircase meet on a little square. "
     + "The little stream is floating under a bridge on the west side of "
     + "the square. Kingsroad continues upwards around the hill to the "
     + "southwest and downwards to the southeast. The staircase continues "
     + "upwards to the south and downwards to the north.";
   make_the_room();
   add_exit(EDORAS_DIR + "path5","southwest",0);
   add_exit(EDORAS_DIR + "path4","southeast",0);
   add_exit(EDORAS_DIR + "stairs2","south",0);
   add_exit(EDORAS_DIR + "stairs1","north",0);
   reset_room();
}

void
reset_room() 
{
   object kid;
   if (!present("kid", TO)) 
   {
      kid = clone_object(EDORAS_DIR + "npc/child");
      kid->arm_me();
      kid->move_living("down", TO);
   }
}


