#pragma save_binary

inherit "/d/Shire/room.c";
#include "/d/Shire/common/defs.h"
#include "trickster.h"

void
create_room()
{
   set_short("End of a hallway");
   set_long(
      "The hallway comes to a sudden end.  This room looks very strange.. " +
      "There are pillows scattered all over the room... most of them " +
      "gathered in a pile underneath a hole, which has been dug in the " +
      "ceiling.  But the thing which strikes you as the most out of place " +
      "in this room, is a wooden panel which lies against the south wall. " +
      "The only obvious way out of here is to head back the way you came.\n");
   
   add_item("hole", "The hole is a rather dark one, just about " +
      "the proper size for a person to fit into.  It resides just above " +
      "you in the ceiling hanging over a pile of pillows which are scattered " +
      "across the floor.\n");
   add_item(({"wall","panel","wall panel"}),
      "Hmmm... part of the wall is a wooden panel..  It seems out of place here "+
      "in the room, where all the other walls are of earth.  Upon closer " +
      "examination of the panel you notice that it looks very loose and " +
      "you might be able to give it a push.\n");
   
   add_item("pillows", "A pile of pillows lie scattered across the " +
      "ground, a pile of them lie directly underneath a hole in the " +
      "ceiling\n");
   
   add_prop(ROOM_I_INSIDE, 1);
   
   add_exit(TRICK_DIR + "hallway","north",0,1);
   
}

void
enter_inv(object ob, object from)
{
   ::enter_inv(ob, from);
   if (!living(ob))
      return;
   if (file_name(from) == TRICK_DIR + "slide")
      {
      ob->command("$scream");
      say(QCTNAME(ob) + " falls from a hole in the ceiling and " +
         "lands safely on some nearby pillows.\n",ob);
      ob->catch_msg("You land safely on a pile of pillows and your " +
         "eventful slide is finally at an end.\n");
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
   if (str == "wall" || str == "panel" || str == "wall panel")
      {
      
      tell_room(TO, QCTNAME(TP) + " is flipped upside-down and " +
         "engulfed by the wall, as " + HE_SHE(TP) + " pushes against it.\n",TP);
      TP->move_living("M", TRICK_DIR + "ladder_room");
      return 1;
   }
   write("Push the panel maybe?\n");
   return 1;
}
