inherit "/std/room.c";
#include "/d/Rhovanion/defs.h"
void
create_room() {
   set_short("monster, monster, monster trucks!!!\n");
   set_long("You round the bend in the passageway and " +
      "see the passage continues far, far to the east.  It " +
      "is a bit warmer here, perhaps more moist as well.\n");
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_LIGHT, 0);
   add_item(({"block","blocks"}),"These are large, dark blocks of stone " +
      "approximately one by two feet in dimension.  They all appear to " +
      "be nearly identical so you figure they must have been worked on " +
      "by a master stoneworker.\n");
   clone_object("/d/Rhovanion/mute/dungeon1/wguard11.c")->move(TO);
   clone_object("/d/Rhovanion/mute/dungeon1/wguard11.c")->move(TO);
   add_exit("/d/Rhovanion/mute/dungeon1/guard22","south");
   add_exit("/d/Rhovanion/mute/dungeon1/guard26","east","@@p_check");
}
int p_check() {
   if(TP->query_npc()) { return 0; }
   if (present("guard",TO))
      {
      write("The wyrmman lowers its spear blocking the " +
         "corridor and preventing you from going east.\n");
      say(QCTNAME(TP)+" is prevented from going east as " +
         "the solemn, reptilian wyrmman lowers its spear " +
         "to block the passageway.\n");
      return 1;
   }
   return 0;
}
