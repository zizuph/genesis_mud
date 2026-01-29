inherit "/std/room.c";
#include <ss_types.h>
#include "/d/Rhovanion/defs.h"
void
create_room() {
   set_short("Property of Mute!\n");
   set_long("This is a small room approximately fifteen " +
      "feet square in size with large, stone blocks for the " +
      "walls and ceiling and a solid stone floor.  A pair " +
      "of well-made straw tatami mats lie against the west wall " +
      "and hanging from the north wall is an old scroll. It " +
      "smells oddly rank in here.\n");
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_LIGHT, 0);
   add_item(({"block","blocks"}),"These are large, dark blocks of stone " +
      "approximately one by two feet in dimension.  They all appear to " +
      "be nearly identical so you figure they must have been worked on " +
      "by a master stoneworker.\n");
   add_item("scroll","This old parchment hangs open from " +
      "the wall and bears a few lines of writing in a strange " +
      "language you've never seen before.\n");
   add_item(({"mat","mats"}),"These are mats of long straws tied " +
      "together with strings horizontally.  You could use " +
      "one to sleep on if you were desperate.\n");
   clone_object("/d/Rhovanion/mute/dungeon1/door4a.c")->move(TO);
clone_object("/d/Rhovanion/mute/dungeon1/wguard3.c")->move(TO);
   clone_object("/d/Rhovanion/mute/dungeon1/wguard4.c")->move(TO);
   clone_object("/d/Rhovanion/mute/dungeon1/wchest2.c")->move(TO);
}
void
init()
{
   ::init();
   add_action("try_read","read");
}
int
try_read(string str) {
   notify_fail("Read what?\n");
   if (!str)
      return 0;
   if (str != "scroll")
      return 0;
   if (this_player()->query_skill(SS_LANGUAGE) <=25)
      {
      write("You don't understand what it says.\n");
      say(QCTNAME(this_player()) + " smells his finger.\n");
      return 1;
   }
   write("It says: \n" +
      "          Live to serve the Master!\n" +
      "          \n" +
      "          Many-armed Lord of all!\n" +
      "          \n" +
      "          Devour!\n");
   return 1;
}
