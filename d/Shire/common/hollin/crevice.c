#include "rom.h"

void reset_room();

create_rom()
{
   set_short("Bear cave");
   set_long("You have entered a small bear cave!\n" +
      "Luckily for you however, the bear seems to have gone. "+
      "You notice the soft grass lying on the ground here, "+
      "obviously for the bear to lie comfortable during the "+
      "winter. Another feature of this little cave is a slippery "+
      "upward going hole which leads up into the darkness.\n");
   add_item(({"grass", "floor"}),
      "It looks very comfortable, though I don't think you should "+
      "wait for the bear..\n");
   add_item(({"hole"}),
      "Hmm, it is amazingly sharp and slippery.  You doubt "+
      "that you would be able to climb up there.\n");
   WEST("steep_path");
   reset_room();
}

init()
{
   ::init();
   add_action("do_climb", "climb");
}

int
do_climb(string arg)
{
   if (arg == "up" || arg == "hole" || arg == "up the hole" || arg == "upwards") 
      {
      write("You start to climb upwards.\n");
      say(QCTNAME(TP) + " starts climbling upwards.\n");
      write("However, you soon lose foothold, and slide down again..\n");
      say(QCTNAME(TP) + " arrives landing on the soft grass...\n");
      return 1;
   }
   else
      return notify_fail("Climb what?\n");
}

void
reset_room()
{

}
