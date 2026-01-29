inherit "/std/room.c";
#include "/d/Rhovanion/defs.h"
int recently_searched;
void
create_room() {
   set_short("read it, boyee!\n");
   set_long("The passageway ends here in what appears to be a cave-in.  Rocks, dust, and stone are piled from ceiling to floor blocking off access to the east.  The air is particularly dusty, filled with black dust from the cave-in.  You wonder if there is a chance for another cave-in and it makes you a bit uneasy.\n");
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_LIGHT, 0);
   add_item(({"rock","rocks","dust","stone","cave-in"}),"You examine the debris of the cave-in and decide it best to leave well enough alone.  You calculate that the risk of another cave-in is too great to be poking around through this rubbage.\n");
   add_exit("/d/Rhovanion/common/dungeon1/rooms/spilair7","west");
}
void
init()
{
   ::init();
   add_action("part_corpse","search");
}
int
part_corpse(string str)
{
   if(!str || str != "cave-in")
      return 0;
   if(recently_searched)
      {
      write("You search through the rubble and debris of the " +
         "cave-in only to succeed in covering yourself with dirt.\n");
      return 1;
   }
   write("You begin to search through the debris of the cave-in...\n");
   say(QCTNAME(TP) + " begins to search through the debris of the cave-in.\n");
   call_out("part_find",3);
   return 1;
}
string
part_find() {
   recently_searched = 1;
   write("You find a body in the debris and pull it out.\n");
   say(QCTNAME(TP) + " uncovers a body in the debris and pulls it out.\n");
   room_add_object("/d/Rhovanion/common/dungeon1/gear/corpse2.c",1,
      "It looks pretty smushed.\n");
   return "";
}
