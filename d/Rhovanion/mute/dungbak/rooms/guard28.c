inherit "/std/room.c";
#include "/d/Rhovanion/defs.h"
void
create_room() {
   set_short("Mute's place.\n");
   set_long("You are at the entrance to a long, dark " +
      "tunnel heading north.  The passageway is constructed " +
      "of large, stone blocks, is very warm, and reaks of " +
      "a foul wyrm-like odour.  The hair on your neck " +
      "raises at the thought of what could be down this " +
      "tunnel.\n");
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_LIGHT, 0);
   add_item(({"block","blocks"}),"These are large, dark blocks of stone " +
      "approximately one by two feet in dimension.  They all appear to " +
      "be nearly identical so you figure they must have been worked on " +
      "by a master stoneworker.\n");
   clone_object("/d/Rhovanion/mute/dungeon1/door7.c")->move(TO);
   add_exit("/d/Rhovanion/mute/dungeon1/guard29","north");
}
