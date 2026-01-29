inherit "/std/room.c";
#include <ss_types.h>
#include "/d/Rhovanion/defs.h"
void
create_room() {
   set_short("Property of Mute!\n");
   set_long("You have entered a small room about fifteen " +
      "by twenty feet in size.  The large, stone blocks that " +
      "are its walls and ceiling are smooth and well-polished. " +
      "Upon a cushion by the south wall lies an unfurled " +
      "tatami mat and a scroll hangs just above it.  There is " +
      "also a pile of cushions sitting in the southeast corner. " +
      "It smells a bit rank in here and is quite warm.\n");
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_LIGHT, 0);
   add_item(({"block","blocks"}),"These are large, dark blocks of stone " +
      "approximately one by two feet in dimension.  They all appear to " +
      "be nearly identical so you figure they must have been worked on " +
      "by a master stoneworker.  These stones in particular " +
      "appear smooth and well-polished.\n");
   add_item("scroll","This old parchment hangs open from " +
      "the wall and bears a few lines of writing in a strange " +
      "language you've never seen before.\n");
   add_item("mat","This is a mat of long straws tied " +
      "together with strings horizontally.  You could use " +
      "one to sleep on if you were desperate.  This one in " +
      "particular looks pretty well made.\n");
   add_item("cushions","These are small variously shaped " +
      "fluffy cushions piled in the southeast corner.  They " +
      "look comfortable enough to curl up on and go to sleep.\n");
   clone_object("/d/Rhovanion/mute/dungeon1/wguard12.c")->move(TO);
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
      "          Oh, blessed Master!\n" +
      "          \n" +
      "          Grant us the gifts of Feorol!\n" +
      "          \n" +
      "          Devour!\n");
   return 1;
}
