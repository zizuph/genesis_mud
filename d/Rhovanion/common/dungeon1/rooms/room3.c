inherit "/std/room.c";
#include "/d/Rhovanion/defs.h"
#include <ss_types.h>
#include <macros.h>
static int snake_fought=1;
static int snake_on=1;
static int portcullis=1;
void
create_room() {
   portcullis=1;
   set_short("black hole\n");
   set_long("You have entered a twenty by twenty room of " +
      "large, stone blocks flooded with two feet of water. " +
      "A large, stone boulder carved roughly into the shape of " +
      "a rectangle lies against the west wall, and from the north " +
      "wall protrudes a short, wooden lever.\n");
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_LIGHT, 0);
   add_item("portcullis","This is a rusted, old portcullis " +
      "that looks like it's still pretty sturdy.\n");
   add_item("boulder","This is a large, stone boulder carved " +
      "roughly like one of the large, stone blocks in the walls. " +
      "It is leaning against the west wall.\n");
   add_item("lever","@@look_lever");
   add_item(({"block","blocks"}), "These large, dark blocks of " +
      "stone approximately one by two feet in dimension are covered " +
      "with brackish green and black molds and drip slime from tiny " +
      "cracks throughout the mortar.\n");
   add_item("stone","The stone in the blocks is very dark and " +
      "lusterless nearly black in color.\n");
   add_item("water","The water is murky, green, and littered with " +
      "pieces of trash you can only guess as to where they came from " +
      "or what they're made of which float on top of the water along " +
      "with a filmy layer of slime.\n");
   add_cmd_item("lever","pull","@@snake_trap");
   clone_object("/d/Rhovanion/common/dungeon1/living/dummy_snake.c")
   ->move(TO);
   clone_object("/d/Rhovanion/common/dungeon1/gear/javelin.c")
   ->move(TO);
   set_alarm(1.0,0.0,"port_down");
}
react_destruct() {
   present("dummy_snake",TO)->react_destruct();
   snake_on=0;
   return 1;
}
port_down() {
   write("A portcullis slams down behind you!\n");
   add_my_desc("There is a portcullis covering the south exit.\n");
}
void
init() {
   ::init();
   add_action("snake_trap","pull");
}
int
snake_trap(string str) {
   notify_fail("Pull what?\n");
   if (!str)
      return 0;
   if (str != "lever")
      return 0;
   if (portcullis==0)
      {
      write("The lever is already down.\n");
      return 1;
   }
   else
      if (present("dummy_snake"))
      {
      write("You put your hand on the lever, but there's a snake " +
         "on it!  You should have looked first.\n");
      present("dummy_snake",TO)->react_destruct();
      snake_on=0;
      snake_fought=0;
      room_add_object("/d/Rhovanion/mute/dungeon1/trap_snake.c");
      return 1;
   }
   else
      {
      portcullis=0;
      write("You pull the lever down and...\n" +
         "The portcullis slowly rises behind you.\n");
      say(QCTNAME(TP) + " pulls down the lever and...\n" +
         "The portcullis slowly rises behind you.\n");
      remove_my_desc();
      add_exit("/d/Rhovanion/common/dungeon1/rooms/int4","south");
      return 1;
   }
}
look_lever() {
   if (portcullis==0)
      return "This is a short, wooden lever.  It has been pulled " +
   "down.\n";
   else
      if (present("dummy_snake"))
      return "This is a short, wooden lever in the upright position. " +
   "A small snake lies coiled upon it.\n";
   else
      return "This is a short, wooden lever in the upright position.\n";
   return 1;
}
/* if dummy_snake not present, then snake_on=0; */
