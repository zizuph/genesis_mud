inherit "/std/room.c";
#include "/d/Rhovanion/defs.h"
void
create_room() {
   set_short("Property of Mute!\n");
   set_long("This is a long, dark corridor of large, stone " +
      "blocks unlike the others you've been in recently as this one " +
      "is a bit cleaner and doesn't smell quite so bad.  You " +
      "glimpse the light of torches to your east.\n");
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_LIGHT, 0);
   add_item(({"block","blocks"}),"These are large, dark blocks of stone " +
      "approximately one by two feet in dimension.  They all appear to " +
      "be nearly identical so you figure they must have been worked on " +
      "by a master stoneworker.\n");
   add_item(({"block","blocks"}),"These are large, dark blocks of stone " +
      "approximately one by two feet in dimension.  They all appear to " +
      "be nearly identical so you figure they must have been worked on " +
      "by a master stoneworker.\n");
   add_exit("/d/Rhovanion/common/dungeon1/rooms/guard5","west");
   add_exit("/d/Rhovanion/common/dungeon1/rooms/guard3","east");
}
