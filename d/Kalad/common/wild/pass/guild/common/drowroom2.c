inherit "/d/Kalad/room_std";
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/wild/pass/guild/defs.h"
object ob1;
object ob2;
object ob3;

void
create_room()
{
set_short("drow room.");
set_long("If you are mortal you shouldn't be here make a bug report! "
	+"Otherwise this is a room where drow clone and wander.\n");
add_exit(DGUILD + "common/joinroom", "south", 0, 1);
add_exit(DGUILD + "common/s2", "northwest", 0, 1);
add_exit(DGUILD + "common/s1", "north", 0, 1);
add_prop(ROOM_I_INSIDE,1);
add_prop(ROOM_NO_TIME_DESC,1);
add_prop(ROOM_I_LIGHT,0);
add_prop(ROOM_M_NO_TELEPORT,1);
set_alarm(1.0,0.0,"reset_room");
}
reset_room()
{
   if (!ob1 || !ob2 || !ob3)
       {
      ob1 = clone_object(DGUILD +"npc/rand_guard.c");
      ob1 ->move_living("xxx", this_object());
      ob2 = clone_object(DGUILD +"npc/rand_guard.c");
      ob2 ->move_living("xxx", this_object());
      ob3 = clone_object(DGUILD +"npc/rand_guard.c");	     
      ob3 ->move_living("xxx", this_object());
	}
}
