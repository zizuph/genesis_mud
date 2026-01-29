inherit "/d/Shire/room.c";
#include "/d/Shire/common/defs.h"
#include "trickster.h"

void
create_room()
{
   set_short("Dark, filthy hole in the ground");
   set_long(
      "This is a very small room filled with disgusting filth.  On the " +
      "northern wall of this room is a wooden panel, and a ladder leading "+
      "upwards are the only things of importance within this room.\n");
   
   add_item("ladder", "A very sturdy ladder.  It looks like it " +
      "could support even the heaviest of persons.\n");
   
   add_item(({"panel","wall","wall panel"}),
      "This panel seems strangely out of place in this earthen hole. " +
      "It looks very strong... you could try giving it a push, but " +
      "it probably won't even budge.\n");
   
   add_item("filth", "The smelly filth lies everywhere in this room. " +
      "It probably would be best if you left it alone.\n");
   
   add_prop(ROOM_I_INSIDE, 1);
   
   add_exit(TRICK_DIR + "s_enterance","up",0,3);
}

void
enter_inv(object ob, object from)
{
   ::enter_inv(ob,from);
   if (!living(ob))
      return;
   if (file_name(from) == TRICK_DIR + "back_way")
      {
      ob->catch_msg("As you push against the panel the bottom of it " +
         "gives out and swings upwards, flipping you around with the wall itself! " +
         "You wind up landing on your head in another room.\n\nOuch!!!\n");
      say("The wooden panel suddenly moves, and "+QTNAME(ob)+" is flung "+
         "into the room and lands on "+HIS_HER(ob)+" head!\n");
   }
}

void
init()
{
   ::init();
   add_action("do_push","push");
}

int
do_push(string str)
{
   if (!str)
      {
      NF("Push what?\n");
      return 0;
   }
   if (str = "wall" || str == "panel" || str == "wall panel")
      {
      write("You push the " +str+ " with all your might but it does not " +
         "budge.  I guess you'll just have to find another way out.\n");
      return 1;
   }
   write("Push what?\n");
   return 1;
}
