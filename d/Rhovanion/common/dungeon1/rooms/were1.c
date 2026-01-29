inherit "/std/room.c";
#include "/d/Rhovanion/defs.h"
void
create_room() {
   set_short("rats!\n");
   set_long("You have entered a seriously decayed and rank " +
      "room for sure.  Strings of gangly, green mosses and slimes " +
      "hang from the ceiling in patches, and the entire place is " +
      "flooded under two or more feet of brack water.  Strange " +
      "foreign shapes move about beneath the water and the floor " +
      "is slimy and mushy.  You can " +
      "hardly feel the stone beneath it.  The air here is foul " +
      "and tainted with the smell of rot, decay, and death.\n");
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_LIGHT, 0);
   add_item("water","The water is murky, green, and littered with " +
      "pieces of trash you can only guess as to where they came from " +
      "or what they're made of which float on top of the water along " +
      "with a filmy layer of slime.\n");
   add_item(({"block","blocks"}), "These large, dark blocks of " +
      "stone approximately one by two feet in dimension are covered " +
      "with brackish green and black molds and drip slime from tiny " +
      "cracks throughout the mortar.\n");
   clone_object("/d/Rhovanion/common/dungeon1/living/wererat.c")
   ->move(TO);
   add_exit("/d/Rhovanion/common/dungeon1/rooms/int8","west");
   add_exit("/d/Rhovanion/common/dungeon1/rooms/were2","north",
      "@@check_rat");
}
int check_rat() {
   if(TP->query_npc()) { return 0; }
   if (present("rat")) {
      write("You splash through the water trying to make it to " +
         "the north exit only to have the rat grab you by your " +
         "neck and hurl you back into the water.\n");
      say(QCTNAME(TP)+" makes a dash for the north passage only " +
         "to be grabbed around the neck by the rat and hurled " +
         "back into the water.\n");
      return 1;
   }
   if (present("wererat")) {
      write("You splash through the water trying to make it to " +
         "the north exit only to have the wererat grab you by your " +
         "neck and hurl you back into the water.\n");
      say(QCTNAME(TP)+" makes a dash for the north passage only " +
         "to be grabbed around the neck by the wererat and hurled " +
         "back into the water.\n");
      return 1;
   }
}
