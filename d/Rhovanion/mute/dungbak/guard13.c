inherit "/std/room.c";
#include <ss_types.h>
#include "/d/Rhovanion/defs.h"
void
create_room() {
   set_short("Property of Mute!\n");
   set_long("This is a small room approximately fifteen " +
      "feet square in size with large, stone blocks for the " +
      "walls and ceiling and a solid stone floor.  A well-made " +
      "straw tatami mat lies against the south wall and hanging " +
      "from the west wall is an old scroll.  It smells oddly " +
      "rank in here.\n");
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_LIGHT, 0);
   add_item(({"block","blocks"}),"These are large, dark blocks of stone " +
      "approximately one by two feet in dimension.  They all appear to " +
      "be nearly identical so you figure they must have been worked on " +
      "by a master stoneworker.\n");
   add_item("mat","This is a mat of long straws tied " +
      "together with strings horizontally.  You could use " +
      "it to sleep on if you were desperate.\n");
   add_item("scroll","This old parchment hangs open from " +
      "the wall and bears a few lines of writing in a strange " +
      "language you've never seen before.\n");
   clone_object("/d/Rhovanion/mute/dungeon1/door3a.c")->move(TO);
   clone_object("/d/Rhovanion/mute/dungeon1/wguard3.c")->move(TO);
   clone_object("/d/Rhovanion/mute/dungeon1/wchest.c")->move(TO);
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
      "          Oh, Goddess of the Wind!\n" +
      "          \n" +
      "          Devour!\n");
   return 1;
}
