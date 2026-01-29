inherit "/std/room.c";
#include "/d/Rhovanion/defs.h"
void
create_room() {
   int i;
   object ob1;
   set_short("lair");
   set_long("It would seem you have found the base lair of the spiders " +
      "living here as there are hordes of webs hanging about from the " +
      "walls, ceiling, and floor.  And not just ordinary webs mind you, " +
      "but enormous webs with strands thick as your finger and strong " +
      "as the strongest ropes.  Your mind fills with fear as you contemplate " +
      "what horrid beasts reside here.\n");
   add_item(({"wall","walls","ceiling","floor"}), "They're too covered with webs for you to be able to see them clearly.\n");
   add_item(({"web","webs"}), "The webs cover this room, and, despite " +
      "the fact they're threatening to encompass you and the entire room, " +
      "seem to possess an unnerving and startling beauty.\n");
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_LIGHT, 0);
   add_exit("/d/Rhovanion/common/dungeon1/rooms/spilair9","up");
   add_exit("/d/Rhovanion/common/dungeon1/rooms/spilair10a","west",
      "@@part_check");
   add_exit("/d/Rhovanion/common/dungeon1/rooms/spilair10b","south",
      "@@part_check");
   add_exit("/d/Rhovanion/common/dungeon1/rooms/spilair10c","east",
      "@@part_check");
   for (i = 0; i < 3; i++)
   ob1 = clone_object("/d/Rhovanion/common/dungeon1/living/spider.c")
   ->move(TO);
}
int part_check() {
   if(TP->query_npc()) { return 0; }
   if(TP->query_name() != "spider")
      if (present("mute_spider",TO))
      {
      write("A spider throws a web over that exit preventing you from reaching it!\n");
      say(QCTNAME(TP)+" tries to leave, but is stopped as a spider throws a web up blocking the exit!\n");
      return 1;
   }
   return 0;
}
