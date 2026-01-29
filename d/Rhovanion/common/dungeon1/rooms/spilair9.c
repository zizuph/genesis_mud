inherit "/std/room.c";
#include "/d/Rhovanion/defs.h"
#define MAX_NO_SERV 3
void do_add_exits();
void do_remove_exits();
int p_stone, called;
reset_room() {
   if (p_stone)do_remove_exits();
   p_stone = 0;
   called = MAX_NO_SERV;
}
create_room() {
   set_short("Rothole\n");
   set_long("You find yourself now in a small `natural' looking cavern of dark stone.  Laying in small piles or alone are many dark rocks of various size littering the floor.\n");
   add_item(({"piles","rocks"}),"You look through the piles of rocks strewn across the floor and find nothing unusual.  A larger sized stone in the southeast corner catches your eye though.\n");
   add_item(({"stone","large stone"}),"This stone appears to be lying over top of a dark, dark hole.  Perhaps, if you're strong enough, brave enough, you may be able to lift it.\n");
   add_item(({"wall","walls"}),"The walls upon closer inspection reveal strange almost chisel like scars.  If this is really a natural cavern then it must truly be unique.\n");
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_LIGHT, 0);
   add_exit("/d/Rhovanion/common/dungeon1/rooms/spilair7","north");
   add_cmd_item("hole","enter","@@enter_hole");
   add_cmd_item("stone","lift","@@lift_stone");
   p_stone = 0;
   called = MAX_NO_SERV;
}
do_add_exits() {
   seteuid(getuid());
   TO->add_exit("/d/Rhovanion/common/dungeon1/rooms/spilair10","hole",0);
   TO->add_my_desc("A large stone has been overturned revealing a hole leading down into darkness.\n");
}
void
do_remove_exits() {
   seteuid(getuid());
   TO->remove_exit("hole");
   TO->remove_my_desc();
}
lift_stone() {
   if (p_stone) {
      say(QCTNAME(TP) + "turns a large stone in the southeast corner over dropping it back over the dark hole.\n");
      write("You turn the large stone back over the hole and re-cover it.\n");
      do_remove_exits();
      p_stone = 0;
      return 1;
   }
   say(QCTNAME(TP) + "overturns a large stone in the southeast corner over with a loud `Clunk!' as it covers the hole in the floor up.\n");
   write("You overturn the large stone to reveal a dark hole leading down.\n");
   do_add_exits();
   p_stone = 1;
   return 1;
}
enter_hole() {
   TP->move_living("into the hole","/d/Rhovanion/common/dungeon1/rooms/spilair10.c");
   return 1;
}
