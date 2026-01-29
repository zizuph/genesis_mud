inherit "/std/room.c";
#include "/d/Rhovanion/defs.h"
void
create_room() {
   set_short("Rompus Maximus.\n");
   set_long("It is rather cold in this turn in the passageway. " +
      "Dust covers the old, stone blocks of the walls, and an " +
      "unearthly odour fills your nostrils almost making you gag.\n");
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_LIGHT, 0);
   add_item(({"block","blocks"}),"These are large, dark blocks of stone " +
      "approximately one by two feet in dimension.  They all appear to " +
      "be nearly identical so you figure they must have been worked on " +
      "by a master stoneworker.\n");
   clone_object("/d/Rhovanion/common/dungeon1/living/gwarrior.c")->move(TO);
   add_exit("/d/Rhovanion/common/dungeon1/rooms/cell15","north","@@part_check");
   add_exit("/d/Rhovanion/common/dungeon1/rooms/cellint1","east");
}
int part_check() {
   if(TP->query_npc()) { return 0; }
   if (present("warrior",TO))
      {
      write("A searing red light suddenly emanates from the creature's " +
         "eyes and you freeze in fear!\n");
      say(QCTNAME(TP)+ " tries to get by the creature but stops in fear " +
         "as he is blasted by a searing red light from the creature's eyes!\n");
      return 1;
   }
   return 0;
}
