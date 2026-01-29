inherit "/std/room.c";
#include "/d/Rhovanion/defs.h"
void
create_room() {
   set_short("int\n");
   set_long("This is a small alcove set into the west wall of " +
      "this turn in the passage with a slim tunnel leading out of " +
      "it to the northeast.  It is empty but for the ever present " +
      "large, stone blocks of the walls and ceiling.\n");
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_LIGHT, 0);
   add_item(({"block","blocks"}),"These are lage, dark blocks of stone " +
      "approximately one by two feet in dimension.  They all appear to " +
      "be nearly identical so you figure they must have been worked on " +
      "by a master stoneworker.\n");
   clone_object("/d/Rhovanion/common/dungeon1/living/wguard1.c")
   ->move(TO);
   add_exit("/d/Rhovanion/common/dungeon1/rooms/int12","northeast",
      "@@check_guard");
   add_exit("/d/Rhovanion/common/dungeon1/rooms/int11","east");
}
int check_guard() {
   if(TP->query_npc()) { return 0; }
   if (present("guard")) {
      write("The guard is blocking that exit.\n");
      say(QCTNAME(TP)+" tries to go northeast, but the guard blocks him.\n");
      return 1;
   }
}
