inherit "/std/room.c";
#include "/d/Rhovanion/defs.h"
void
create_room() {
   set_short("Ha!\n");
   set_long("This is a small little dugout chamber filled with " +
      "dark wet dirt.  The west wall appears to have once supported " +
      "some sort of tunnel that has now collapsed.  Piles of dark " +
      "dirt lie strewn about as it appears someone has been digging " +
      "trying to reopen the tunnel.  Roots stick out from the wall " +
      "everywhere along with worms and the occasional grotesque insect. " +
      "It is unusually dark here and eerie.\n");
   add_item(({"root","roots"}),"The roots stick out of the dirt " +
      "everywhere.  They're particularly twisted, dark, and odd, and you " +
      "don't ever recall having seen their like " +
      "before leaving you wondering what the plant they belong to must " +
      "look like.\n");
   add_item("dirt","This is unusually dark and wet dirt. " +
      "You've never in all your life seen its like before.\n");
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_LIGHT, 0);
   add_exit("/d/Rhovanion/common/dungeon1/rooms/bantun1","south");
   clone_object("/d/Rhovanion/common/dungeon1/living/bandit3.c")
   ->move(TO);
   clone_object("/d/Rhovanion/common/dungeon1/living/bandit4.c")
   ->move(TO);
}
