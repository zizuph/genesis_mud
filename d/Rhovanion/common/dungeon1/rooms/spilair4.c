inherit "/std/room.c";
#include "/d/Rhovanion/defs.h"
void
create_room()
{
   set_short("platinum pile\n");
   set_long("This is what appears to be a natural cavern.  The floor is fairly smooth and the walls unnaturally shaped.  What catches your eye though is the odd nooks and crannies that litter the ceiling offering a myriad of hiding places for who knows what!\n");
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_LIGHT, 0);
   add_item("ceiling","Aside from the myriad of nooks and crannies in the ceiling, your eye focuses upon a group of small rocks that appear to be jammed into a section of the ceiling.\n");
   add_item(({"rock","rocks","small rocks"}),"You are clueless as to how these rocks got here, but it looks as if you might be able to pull them out of the hole they're jammed in.\n");
   add_exit("/d/Rhovanion/common/dungeon1/rooms/spilair3","east");
   add_cmd_item("rocks","pull","@@pull_rocks");
}
string
pull_rocks() {
   say(QCTNAME(TP) + "pulls some rocks from the ceiling\n" +
      "The rocks pour out of the ceiling all over" + QCTNAME(TP) + "along with some other items of interest...\n");
   write("You pull the rocks from their nook in the ceiling...\n" +
      "The rocks pour down all over you bruising you a little...\n");
   this_player()->heal_hp(-25);
   set_alarm(1.0,0.0,"part_one");
   return "";
}
string
part_one() {
   room_add_object("/d/Rhovanion/common/dungeon1/gear/orb.c", 1,
      "A glowing orb falls from the nook in the ceiling followed by...\n");
   set_alarm(1.0,0.0,"part_two");
}
string
part_two() {
   room_add_object("/d/Rhovanion/common/dungeon1/living/spihorde.c", 1,
      "...a horde of spiders!\n");
   set_alarm(0.0,0.0,"part_three");
   return "";
}
public int
part_three() {
   remove_cmd_item("rocks");
   add_cmd_item("rocks","pull","@@pull_rocks2");
   return 1;
}
string
pull_rocks2() {
   write("You think if you keep pulling on more rocks you might start a cave-in so you refrain.\n");
   return "";
}
