inherit "/std/room";

#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "defs.h"

int trap_open;

create_room() {
   set_short("little house");
   set_long("@@my_long");

   add_item("door", break_string(
      "The door is made of oak and has rusty hinges. It is round, just like "
    + "the window next to it.\n",70));

   add_item("trapdoor", "@@trap_desc");

   add_item("window", break_string(
      "Like the door, the window has a round shape. Through it you see "
    + "the southern center of the little village.\n",70));

   add_item(({"red cord", "cord"}), break_string(
      "The red cord hangs down from the roof, and doesn't seem to serve "
    + "any purpose at all. It looks like you can pull it.\n",70));

   add_item(({"painting","paintings"}), break_string(
      "The paintings show pictures of hobbits making wine by treading in "
    + "big barrels filled with grapes.\n",70));

   add_exit(STAND_DIR + "wf_south", "east", "@@make_noise");

   add_prop(ROOM_I_INSIDE, 1); /* This room lies inside */

   trap_open = 0;
}

reset_room() {
   trap_open = 0;
}

init() {
   ::init();
   add_action("do_pull","pull");
   add_action("do_down","down",1);
}

my_long() {
   if (trap_open)
      return break_string(
      "You are inside a little hobbit-house. There is only one window here, "
    + "just next to the door. On the walls are some paintings and on the "
    + "southern wall hangs a red cord. In the middle of the floor is an "
    + "opened trapdoor leading down.\n",70);

   return break_string(
      "You are inside a little hobbit-house. There is only one window here, "
    + "just next to the door. On the walls are some paintings and on the "
    + "southern wall hangs a red cord.\n",70);
}

trap_desc() {
  if (trap_open) return break_string("You look down the hole and estimate "+
    "the distance you will fall when going down the trapdoor. With a sigh of "+
    "relief you see it's not too far away... about six or seven feet.\n", 70);
  return "You find no trapdoor.\n";
}

make_noise() {
   write("The door squeaks as you pull it open.\n");
   say("The door squeaks as " + QCTNAME(this_player()) + " pulls it open.\n");

   seteuid(getuid());      /* You must do this in a VBFC function */
   (STAND_DIR + "wf_south")->open_door();  /* Make noise in the other room */
}

do_down(str) {
   if (str)
      return 0;

   if (!trap_open)
      return 0;

   this_player()->move_living("leaves down.",STAND_DIR + "wf_house1d");
   return 1;
}

open_door() {
   tell_room(this_object(), "The door squeaks as someone pushes it open from the outside.\n");
}

do_pull(str) {
   if (str != "cord" && str != "red cord")
   {
      notify_fail("Pull what?\n");
      return 0;
   }

   write("You pull the red cord.\n");

   if (trap_open)
   {
      write("Nothing happens.\n");
   }
   else
   {
      tell_room(this_object(),"A trapdoor opens in the middle of the floor.\n");
      trap_open = 1;
      set_alarm(300.0, 0.0, open_trap);
   }
   return 1;
}

open_trap()
{
   trap_open = 0;
   tell_room(this_object(),"The trapdoor in the middle of the floor falls shut again.\n");
}
