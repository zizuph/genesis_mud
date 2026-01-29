inherit "/std/room.c";
#include "/d/Rhovanion/defs.h"
void
create_room() {
   set_short("Mute's place.\n");
   set_long("You are traveling in a long, dark " +
      "tunnel running north and south.  The passageway is " +
      "constructed of large, stone blocks, is very warm, " +
      "and reaks of a foul wyrm-like odour.\n");
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_LIGHT, 0);
   add_item(({"block","blocks"}),"These are large, dark blocks of stone " +
      "approximately one by two feet in dimension.  They all appear to " +
      "be nearly identical so you figure they must have been worked on " +
      "by a master stoneworker.\n");
   add_exit("/d/Rhovanion/mute/dungeon1/guard30","north");
   add_exit("/d/Rhovanion/mute/dungeon1/guard28","south");
}
