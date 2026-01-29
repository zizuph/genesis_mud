inherit "/std/room.c";
#include "/d/Rhovanion/defs.h"
void
create_room() {
   set_short("Property of Mute!\n");
   set_long("The large, stone blocked corridor turns here. " +
      "A pair of wooden doors are set into stone archways " +
      "in the west wall and in the south wall.\n");
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_LIGHT, 0);
   add_item(({"block","blocks"}),"These are large, dark blocks of stone " +
      "approximately one by two feet in dimension.  They all appear to " +
      "be nearly identical so you figure they must have been worked on " +
      "by a master stoneworker.\n");
   add_item(({"archway","archways"}),"The archways surround " +
      "the doors for about an inch and a half all the way " +
      "around.  They are made of smooth, dark stone.\n");
   clone_object("/d/Rhovanion/mute/dungeon1/door2.c")->move(TO);
   clone_object("/d/Rhovanion/mute/dungeon1/door3.c")->move(TO);
   add_exit("/d/Rhovanion/mute/dungeon1/guard18","north");
   add_exit("/d/Rhovanion/mute/dungeon1/guard4","east");
}
