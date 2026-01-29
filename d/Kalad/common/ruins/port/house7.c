inherit "/d/Kalad/room_std";
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Kalad/common/zhent/defs.h"
#include "/d/Kalad/defs.h"
object ob1;
object ob2;

void
create_room()
{
set_short("A small house");
set_long("This is a small house, probably owned by a low income family.\n");
add_exit(ZHENT +"port/p25","out");
add_prop(ROOM_I_INSIDE,1);
add_prop(ROOM_NO_TIME_DESC,1);
set_alarm(1.0,0.0,"reset_room");
}
reset_room()
{
   if (!ob1 || !ob2)
      {
      ob1 = clone_object("/d/Kalad/common/zhent/npc/man.c");
      ob1 ->move_living("xxx", this_object());
      ob2 = clone_object("/d/Kalad/common/zhent/npc/woman.c");
      ob2 ->move_living("xxx", this_object());
      }
}
