/*
 *  Path leading to Hin Warrior Guild
 */

inherit "/std/room";

#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "defs.h"

create_room() {
   set_short("Path");
   set_long("@@my_long");

   add_item(({"rock","rocks","rock wall","rock walls", "walls"}), break_string(
      "The rock formations aside the path are way too steep to climb. They "
    + "force you to go either southwest or north.\n",70));

   add_item("big rock","@@rock_long");

   add_item("eagle", break_string(
      "The eagle is flying high over the mountain, looking for a prey "
    + "to feed on. It is probably a friend of the windlord Dondon.\n",70));

   add_item("button", break_string("You can hardly see the button since it "+
      "has virtually the same color as the rocks. As you examine the button "+
      "carefully, you notice the word 'close' is engraved in it.\n", 70));

   add_exit(HINROOM_DIR + "path1","north");
   add_exit(HINROOM_DIR + "path3","southwest","@@make_noise");

   add_prop(ROOM_I_INSIDE, 0);  /* This room is outside */

   reset_room();
}

reset_room()
{
   if (!present("rock") && !random(4))
      clone_object(OBJ_DIR + "smallrock")->move(this_object());
}

init() {
  ::init();
  add_action("do_press", "press");
  add_action("do_press", "push");
}

do_press(str) {
  if (str != "button") return 0;
  if (rock_open()) {
    write("You press the button.\n");
    say(QCTNAME(this_player()) + " presses a button.\n");
    close_rock();
    return 1;
  }
  say("Nothing happens...\n");
  write("Nothing happens... You feel pretty stupid.\n");
  return 1;
}

my_long() {
   if(rock_open()) {
      return break_string(
         "You are standing on a rocky path that winds up the mountain. "
       + "The path is formed by steep rock walls on both sides of it. "
       + "High above the mountain you see an eagle flying. To the north the "
       + "path leads up, southwest the path winds down the mountain. "
       + "You notice a button well hidden in the rocks.\n",70);
   }
   else {
      return break_string(
         "You are standing on a rocky path that winds up the mountain. "
       + "The path is formed by steep rock walls on both sides of it. "
       + "High above the mountain you see an eagle flying. To the north "
       + "the path leads up, southwest the path winds down the mountain "
       + "over a climbable big rock. You notice a button well hidden "
       + "in the rocks.\n",70);
   }
}

rock_long() {
   if(rock_open())
      return "You find no big rock.\n";
   else {
      return break_string(
         "The big rock is blocking the path to the southwest, but is seems "
       + "climbable from this side of it.\n",70);
   }
}

rock_open() {
 /* This function is called by a Value By Function Call procedure,
    so we must set the euid to be able to use a call_other ('->')
 */
   seteuid(getuid());
   return (HINROOM_DIR + "path3")->query_rock_open();
}

make_noise() {
   if(!rock_open())
      write("You climb over the big rock and fall down on the other side of it.\n");
   return 0;
}

close_rock() {
  seteuid(getuid());
  (HINROOM_DIR + "path3")->close_rock();
  tell_room(this_room(), "The rock closes with a mechanical sound.\n");
}
