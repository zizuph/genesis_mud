/*
 *  Path leading up the mountain
 */

inherit "/std/room";

#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "defs.h"

int rock_open, good_cnt;

create_room() {
   rock_open = 0;
   set_short("Path");
   set_long("@@my_long");

   add_item(({"big rock","rock"}),"@@rock_long");

   add_item(({"rocks","rock walls"}),"@@rock_long");

   add_item("crevice", "@@crevice_long");

   add_item("hatch", break_string(
      "Behind the hatch, in the rock wall are five coloured buttons. "
    + "The buttons seem to be connected to a mechanical system that is "
    + "able to turn the rock aside. Perhaps you need to press the right "
    + "buttons in the right order...\n",70));

   add_item(({"buttons","coloured buttons"}),
      "The five buttons are coloured red, yellow, white, green and blue.\n");

   add_item(({"red","red button"}),
      "The red button looks worn. It can be pressed.\n");

   add_item(({"yellow","yellow button"}), break_string(
      "The yellow button looks like it has been used less than the others. "
    + "It can be pressed.\n",70));

   add_item(({"white","white button"}),
      "The white button has been used often. It looks pressable.\n");

   add_item(({"green","green button"}),
      "The green button seems to be used seldomly. You can press it.\n");

   add_item(({"blue","blue button"}),
      "The blue button has been used frequently. It can be pressed.\n");

   add_exit(HINROOM_DIR + "path2","northeast","@@check_northeast");
   add_exit(HINROOM_DIR + "path4","south");

   add_prop(ROOM_I_INSIDE, 0);  /* This room is outside */
   add_prop(OBJ_S_WIZINFO,"@@wizinfo");

   reset_room();
}

reset_room()
{
   if (!present("rock") && !random(4))
      clone_object(OBJ_DIR + "smallrock")->move(this_object());
}

init() {
   ::init();
   add_action("do_press","press",0);
   add_action("do_press","push",0);
}

wizinfo() {
   return "These commands will open the way northeast:\n"
    + "  press red button, press white button, press blue button.\n";
}

my_long() {
   if(rock_open) {
      return break_string(
         "You stand between high rock walls that leave you only two "
       + "options: either go northeast, up the mountain, or south, down "
       + "the mountain. To your right is something in the rock wall that "
       + "looks like a hatch.\n",70);
   }
   else
      return break_string(
         "You are standing before a dead end. Here a big rock is blocking "
       + "your way northeast. It seems impossible to move the rock. "
       + "To your right is something that looks like a hatch. The only "
       + "way out of here is south, down the mountain, because big rock walls "
       + "block all other exits.\n",70);
}

rock_long() {
   if(rock_open)
      return rock_walls();
   else
      return break_string( 
         "The big rock blocks the path to the northeast. Through a little "
       + "crevice you can see that the path continues on that side of the "
       + "rock. The rock is far too big to push it aside. There has to "
       + "be another way to move the rock...\n",70);
}

crevice_long() {
   if (rock_open)
      return "You find no crevice.\n";
   else
      return "The crevice proves that there is a path behind the rock.\n";
}

rock_walls() {
   return break_string(
      "The huge rock walls are far too steep to climb without the necessary "
    + "climbing gear. In the rock wall to your right side is something "
    + "that looks like a hatch.\n",70);
}

query_rock_open() {
   return rock_open;
}

close_rock() {
   remove_call_out("close_rock");
   if (rock_open)
   {
      rock_open = 0;
      tell_room(this_room(), "The rock closes with a mechanical sound.\n");
   }
}

/* Press the button of a certain colour.
 * The right order in which the buttons have to be pressed is RED-WHITE-BLUE.
 * Pressing any wrong button will reset the keys you already have pressed.
 * A side-effect of this is that red-green-yellow-yellow-red-white-blue
 * will also work. Note that two people pressing buttons at the same time
 * can mess up eachothers (maybe correct) order.
*/ 

do_press(str) {
   string colour;

   notify_fail(capitalize(query_verb()) + " what?\n");

   if (!str || str == "")
      return 0;

   if (!sscanf(str,"%s button",colour))
      colour = str;

   if (colour == "red") {
      make_press_sounds(colour);
      tell_room(this_object(),"Nothing happens.\n");
      if (good_cnt)
         good_cnt = 1;
      else
         good_cnt++;
      return 1;
   }      

   if (colour == "yellow") {
      good_cnt = 0;
      make_press_sounds(colour);
      tell_room(this_object(),"Nothing happens.\n");
      return 1;
   }

   if (colour == "white") {
      make_press_sounds(colour);
      tell_room(this_object(),"Nothing happens.\n");
      if (good_cnt == 1)
         good_cnt++;
      else
         good_cnt = 0;
      return 1;
   }      

   if (colour == "green") {
      good_cnt = 0;
      make_press_sounds(colour);
      tell_room(this_object(),"Nothing happens.\n");
      return 1;
   }

   if (colour == "blue") {
      make_press_sounds(colour);
      if (good_cnt == 2 && !rock_open) {
         tell_room(this_object(), break_string(
            "Suddenly the big rock starts to move. With a mighty noise, it "
          + "turns away from the path, allowing you to go northeast.\n",70));
         rock_open = 1;
         call_out("close_rock",30); /* Close automatically */
      }
      else
         tell_room(this_object(),"Nothing happens.\n");
      good_cnt = 0;
      return 1;
   }      

   return 0;
}

make_press_sounds(colour) {
   write("You press the " + colour + " button.\n");
   say(QCTNAME(this_player()) + " presses a " + colour + " button.\n");
}

/* Prevent people from going northeast if the rock is blocking the way */

check_northeast() {
   if(rock_open)
      return 0;
   seteuid(getuid());
   if ((SHIRE_PIPE)->is_a_shire(this_player()))
      return 0;
   write("You try to climb the big rock to the northeast but only get\n"
       + "about halfway, before you fall down again.\n");
   say(QCTNAME(this_player()) + " tries foolishly to climb\n"
       + "the big rock to the northeast and falls down again.\n");
   return 1;
}
