inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by Milashk, modified by Antharanos */
   create_room()
{
   set_short("A dirty house");
   set_long("You've entered an extremely dirty home. The entire house "+
      "consists of just this one room. Scattered around the room are "+
      "several pieces of furniture, such as a bed, a small table and a "+
      "rusty old stove.\n");
   add_item(({"furniture"}),
      "There is a bed, a table and a stove, which would you like to look "+
      "at?\n");
   add_item(({"bed"}),
      "A small five foot long bed that has no sheets and is nothing more "+
      "than an iron frame with a thin mattress atop it.\n");
   add_item(({"thin mattress","mattress"}),
      "The filthy fabric is riddled with holes.\n");
   add_item(({"small table","table"}),
      "The tiny wooden table is covered with dust.\n");
   add_item(({"rusty old stove","rusty stove","old stove","stove"}),
      "A worn-out contraption that looks to be nearly three decades old. "+
      "Judging by its rusted outer surface, it appears to be little used.\n");
   add_exit(TRADE(cliff_connect2),"west",0,-1,1);
   hear_bell = 1;
   INSIDE;
   add_prop(ROOM_NO_TIME_DESC,1);
   set_alarm(2.0,0.0,"msg");
}
msg()
{
   tell_room(TO,"As you enter the house, a small woman cowers in the corner, "+
      "then suddenly speeds out the door.\n");
   return 1;
}
