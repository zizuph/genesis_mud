inherit "/std/room.c";
#include "/d/Rhovanion/defs.h"
void
create_room() {
   set_short("room");
   set_long("You crawl through the filthy, dirt tunnel and emerge " +
      "here in some sort of a tunneled out little cavern whose " +
      "ceiling barely gives you any headroom and you're bending " +
      "down already!  Strange twisted roots hang down from the " +
      "ceiling and stick out of the walls unnerving you as you " +
      "brush by them and get dirt on your clothing.\n" +
      "     It looks like whoever dug this tunnel threw a hell of " +
      "a lot of dirt into this room.  In fact you figure that's what they dug " +
      "this room for in the first place.\n");
   add_item(({"root","roots"}),"The roots stick out of the dirt " +
      "everywhere.  They're particularly twisted, dark, and odd, and you " +
      "don't ever recall having seen their like " +
      "before leaving you wondering what the plant they belong to must " +
      "look like.\n");
   add_item("dirt","This is unusually dark and wet dirt. " +
      "You've never in all your life seen its like before.\n");
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_LIGHT, 0);
   add_exit("/d/Rhovanion/common/dungeon1/rooms/room1","east");
   add_exit("/d/Rhovanion/common/dungeon1/rooms/bantun2","north");
}
