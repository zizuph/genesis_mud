inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
create_room()
{
   ::create_room();
   hear_bell = 1;
   set_short("A street");
   set_long("A small and simple little street used to help people see "+
      "how to code a simple room with messages in it.\n");
   add_item(({"small street","simple street","street"}),
      "A small road in the middle of nowhere.\n");
   add_exit("/d/Kalad/workroom","workroom");
   set_alarm(3.0,0.0,"message");
}
message()
{
   tell_room(TO,"A big ball of cow dung falls on your head!\n");
   return 1;
}
