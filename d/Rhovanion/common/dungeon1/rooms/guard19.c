inherit "/std/room.c";
#include "/d/Rhovanion/defs.h"
void
create_room() {
   set_short("Why bother.\n");
   set_long("A heavy air rests upon this dark corridor of " +
      "large, stone blocks.  You feel uneasy standing about " +
      "here.  There is a door set into an archway of stone in " +
      "the west wall.\n");
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_LIGHT, 0);
   add_item(({"block","blocks"}),"These are large, dark blocks of stone " +
      "approximately one by two feet in dimension.  They all appear to " +
      "be nearly identical so you figure they must have been worked on " +
      "by a master stoneworker.\n");
   add_item("archway","The archway surrounds the door for " +
      "about an inch and a half all the way around.  They are " +
      "made of smooth, dark stone.\n");
   clone_object("/d/Rhovanion/common/dungeon1/misc/door5.c")
   ->move(TO);
   add_exit("/d/Rhovanion/common/dungeon1/rooms/guard20","north");
   add_exit("/d/Rhovanion/common/dungeon1/rooms/guard18","south");
}
