inherit "/std/room.c";
#include "/d/Rhovanion/defs.h"
void
create_room() {
   int i;
   object ob1;
   object ob2;
   object ob3;
   set_short("room");
   set_long("You now find yourself in a room approximately twenty " +
      "by twenty feet in area composed of those same large, stone " +
      "blocks so common in these passages.  Looking around you come " +
      "to the conclusion that this is a storeroom.  Barrels, crates, " +
      "and the like lie stacked against the walls.  A thick layer of " +
      "dirt covers the floor in splotches and the barrels " +
      "and crates as well a bit.  \n" +
      "     By the west wall, piled against it, are a few large, " +
      "stone blocks that look as if they were just torn from the " +
      "wall.  Where they should be, low in the southern part of " +
      "the west wall, is a gaping hole large enough for " +
      "a man to crawl through.  Piles of dark, rich looking, moist " +
      "dirt lie just to the sides of the hole.\n");
   add_item(({"block","blocks"}),"These large, dark stoned " +
      "blocks are lying in poor condition up against and by the " +
      "west wall\n");
   add_item(({"barrel","barrels"}),"These very old looking " +
      "barrels contain nothing that hasn't already rotted away.  They " +
      "appear as if they could be shattered with a single blow from a " +
      "weapon.\n");
   add_item(({"crate","crates"}),"These very old looking " +
      "wooden crates might once have contained items of value, " +
      "but are now in a state of total dilapidation.\n");
   add_item("dirt","This is unusually dark and wet dirt. " +
      "You've never in all your life seen its like before.\n");
   add_item("hole","The hole in the west wall looks as if someone " +
      "from the other side bashed it in and came out here.  Peering in " +
      "you see a dark, dirt tunnel leading west.\n");
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_LIGHT, 0);
   clone_object("/d/Rhovanion/common/dungeon1/living/bandit1.c")
   ->move(TO);
   clone_object("/d/Rhovanion/common/dungeon1/living/bandit1.c")
   ->move(TO);
   clone_object("/d/Rhovanion/common/dungeon1/living/bandit2.c")
   ->move(TO);
   add_exit("/d/Rhovanion/common/dungeon1/rooms/tun6","north");
   add_exit("/d/Rhovanion/common/dungeon1/rooms/bantun1","hole",
      "@@part_check");
}
int part_check() {
   if(TP->query_npc()) { return 0; }
   if (present("rogue",TO))
      {
      write("The bandit won't let you by!\n");
      say(QCTNAME(TP)+" tries to leave, but a bandit stops him!\n");
      return 1;
   }
   return 0;
}
