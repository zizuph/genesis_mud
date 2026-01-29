/*
ROOM: South corner of Town Square
DATE: Aug 27, 1994
*/

inherit "/d/Kalad/room_std";

#include "/d/Kalad/defs.h"
object man;

void
create_room()
{
   ::create_room();
   hear_bell = 2;
   
   set_short("The pigeon house");
   set_long(
      "This is a wooden hut where all the mail is sent to "+
      "all over the world, through the use of some reliable "+
      "carrier-pigeons. The letters are attached to the pigeons leg, "+
      "and released by the skilled and friendly hand of the "+
      "trainer of the animals. They flap their wings and fly "+
      "out through a hole in the ceiling, and are off to "+
      "find the receiver of the letter.\n"
   );
   
   
   add_exit(CENTRAL(plaza/post_office), "east",0,-1,-1);
   
   
   add_item(({"pigeon","pigeons"}),
      "These must be carrying letters and messages. You can probably "+
      "buy one for yourself here.\n"
   );
   add_item("hole","Its a large hole in the ceiling, where the pigeons "+
      "flies out.\n");
   set_alarm(0.0,0.0,"reset_room");
}

reset_room()
{
   if(!objectp(man))
      {
      man = clone_object("/d/Kalad/common/central/npc/pigeon_man");
      man -> move_living("M",TO);
      man -> command("emote releases a carrier-pigeon. It flies "+
         "through a hole in the roof.");
   }
}
