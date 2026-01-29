inherit "/std/room.c";
#include "/d/Rhovanion/defs.h"
#include <macros.h>
void
create_room() {
   set_short("Cantankeronsous!\n");
   set_long("This is the south end of a very long room.  It is " +
      "cluttered with dust, rags, and the occasional bone.  Laying " +
      "just south of the west exit is a corroded iron gate.  The " +
      "north part of the room is too dark to see anything in it clearly, " +
      "but a wretched odour of decay seems to be emanating from it.\n");
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_LIGHT, 0);
   add_item(({"block","blocks"}),"These are large, dark blocks of stone " +
      "approximately one by two feet in dimension.  They all appear to " +
      "be nearly identical so you figure they must have been worked on " +
      "by a master stoneworker.\n");
   add_item("rags","These are strips of clothing, pieces of clothing, " +
      "and just in general:  pieces of filth.\n");
   add_item("gate","This once sturdy iron gate is now fallen and " +
      "corroded.  Looking about the room though, you notice a set of " +
      "corroded hinges set into the west exit.\n");
   add_item("hinges","These corroded, iron hinges once held up the " +
      "gate here that now lies on the floor.  They look like the gate " +
      "was ripped right off of them.\n");
   add_exit("/d/Rhovanion/common/dungeon1/rooms/cell18","north");
   add_exit("/d/Rhovanion/common/dungeon2/rooms/cell8","west");
}
