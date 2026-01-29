inherit "/std/room.c";
#include "/d/Rhovanion/defs.h"
void
create_room() {
   int i;
   set_short("Wahoo!\n");
   set_long("This is a small fifteen foot cell devoid of all " +
      "features save the layer of dust covering everything.\n");
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_LIGHT, 0);
   add_item(({"block","blocks"}),"These are large, dark blocks of stone " +
      "approximately one by two feet in dimension.  They all appear to " +
      "be nearly identical so you figure they must have been worked on " +
      "by a master stoneworker.\n");
   for (i = 0; i < 4 + random(2); i++)
   clone_object("/d/Rhovanion/common/dungeon1/living/skeleton1.c")
   ->move(TO);
   clone_object("/d/Rhovanion/common/dungeon1/misc/door8a.c")
   ->move(TO);
}
