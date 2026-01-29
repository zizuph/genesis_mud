/*  -*- LPC -*-  */
/*
 * REMmed out the enter functions
 * -- Finwe, September 7, 2003
 */

#include "defs.h"
#include "/d/Shire/common/include/time.h"

CONSTRUCT_ROOM {
   set_short("By the window");
   set_long("You are standing by the window.  You have a majestic view " +
      "over the scenery from here. From this spot high up in the " +
      "mountain you can see past mountains and valleys out in the " +
      "free, @@describe_scenery@@" +
      "Southwards the Misty Mountains extend, and to the west there " +
      "are the grassy plains of your homeland. (Sniff!) You cannot " +
      "squeeze yourself through the window, but there is a hole in " +
      "the floor here, and a spiral staircase in the south end of " +
      "the room.\n");
   add_item("window","It is impossible to get through, try another way out.");
   add_item(({"hole","floor"}),"It seems you can climb down there.");
   add_item("view",
      "It is the view over the area to the west of Misty Mountains.");
   EXIT("onblock","down");
   EXIT("swindow","south");
/*   
   add_cmd_item(({"through the window","the window","window"}),
      ({"enter", "go", "squeeze" }),"@@my_enter@@");
*/

/*
   add_cmd(({"enter", "climb"}), "[down] [the] 'hole'", "down");
   add_neg("enter", "[down] [the] 'staircase' / 'stairs'",
      "Better go south first then, or?\n");
   add_neg("climb", "[the] 'wall' / 'window'",
      "What on earth do you mean?\n");
*/
   remove_prop(ROOM_I_INSIDE);
}

string
my_squeeze()
{
   say(QCTNAME(TP)+"attempts to squeeze "+HIM_HER(TP)+"self through "+
      "the small window, but fails.\n");
   return "You attempt to squeeze yourself through the small window "+
   "but fail.";
}

void
init()
{
   ::init();
   add_action("do_sniff","sniff");
}

int
do_sniff(string str)
   {
   write("You sniff pitifully, wondering how to get out of these mines.\n");
   say(QCTNAME(TP)+" sniffs pitifully, wondering how to get out of these mines.\n");
   return 1;
}

string describe_scenery()
{
   switch (CLOCK->query_hour()) 
   {
      case EARLY_NIGHT:
      case LATE_NIGHT:
      return "and the clear full moon shines upon the landscape. ";
      case EARLY_MORNING:
      case MORNING:
      return "and the morning sun shines beautifully upon the landscape. ";
      case NOON:
      case AFTERNOON:
      return "and the sun shines magnificiently upon the landscape. ";
      case EVENING:
      default:
      return "and the evening sun descends with red colours into the western hills. ";
   }
}

