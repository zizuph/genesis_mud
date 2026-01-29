inherit "/std/room.c";
#include "/d/Rhovanion/defs.h"
void
create_room() {
   set_short("You enjoy myself!\n");
   set_long("This dark corridor of large, stone blocks " +
      "continues on north and south and tees off to the " +
      "east from where the sound of metal clinging upon " +
      "metal can be heard.  There is a door set into an " +
      "archway of stone in the west wall here as well.\n");
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_LIGHT, 0);
   add_item(({"block","blocks"}),"These are large, dark blocks of stone " +
      "approximately one by two feet in dimension.  They all appear to " +
      "be nearly identical so you figure they must have been worked on " +
      "by a master stoneworker.\n");
   add_item("archway","The archway surrounds the door for " +
      "about an inch and a half all the way around.  They are " +
      "made of smooth, dark stone.\n");
   clone_object("/d/Rhovanion/common/dungeon1/misc/door4.c")
   ->move(TO);
   add_exit("/d/Rhovanion/common/dungeon1/rooms/guard19","north");
   add_exit("/d/Rhovanion/common/dungeon1/rooms/guard7","east");
   add_exit("/d/Rhovanion/common/dungeon1/rooms/guard5","south");
}
