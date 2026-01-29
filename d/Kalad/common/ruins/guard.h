#include "/d/Kalad/common/zhent/defs.h"
#include "/d/Kalad/defs.h"
object ob1;
object ob2;
object ob3;
reset_room()
{
       if (!ob1 || !ob2 || !ob3)
      {
      ob1 = clone_object("/d/Kalad/common/zhent/npc/r_guard.c");
      ob1 ->move_living("xxx", this_object());
      ob2 = clone_object("/d/Kalad/common/zhent/npc/r_guard.c");
      ob2 ->move_living("xxx", this_object());
      ob3 = clone_object("/d/Kalad/common/zhent/npc/r_guard.c");	
      ob3 ->move_living("xxx", this_object());
      ob2 ->team_join(ob1);
      ob3 ->team_join(ob1);
      }
}
