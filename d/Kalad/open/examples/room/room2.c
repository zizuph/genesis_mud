inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
object ob1;
create_room()
{
   ::create_room();
   hear_bell = 1;
   set_short("A street");
   set_long("A small and simple little street used to help people see "+
      "how to code a simple room with an npc in it.\n");
   add_item(({"small street","simple street","street"}),
      "A small road in the middle of nowhere.\n");
   set_alarm(1.0,0.0,"reset_room");
}
void
reset_room()
{
   if(!ob1)
      {
      ob1 = clone_object("/d/Kalad/open/examples/npc/monster1");
      ob1 -> move_living("xxx",TO);
   }
}
