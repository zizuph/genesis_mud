/*
 *   trail03.c
 *
 * Baldacin@Genesis, Nov 2003
 */
#include "ldefs.h"
#include <macros.h>
inherit FORESTSTD;
inherit "/d/Calia/std/room_tell_room";

void
create_room()
{
    set_short("On a wooden bridge");
    set_long("You are walking on a small wooden bridge, "+
      "crossing a small freshwater stream. The trail "+
      "continues in a west-southwest direction.\n");
    
    add_item(({"water","stream","freshwater stream"}), "A little "+
      "bit further downstream the freshwater stream takes "+
      "a sharp turn, changing its flow to the east. It "+
      "should be safe to drink the refreshing water.\n");
    add_item(({"bridge", "wooden bridge"}), "It seems to "+
      "be made of some kind of hardwood tree. Small, yet "+
      "strong and sturdy.\n");
    add_item("trail", "The trail continues in a west-"+
      "southwest direction.\n");
      
    set_tell_time(250);
    add_tell("A small animal scurries quickly from "+
          "one bush to another.\n");
    add_tell("You hear a loud, shrieking sound coming "+
          "from one of the trees.\n");
    add_tell("One of the old trees goes 'Creak, creeek' "+
          "as the wind forces it to sway slowly.\n");
    add_tell("Suddenly everything is very quiet.\n");
       
    add_exit(SFDIR + "trail04","west");
    add_exit(SFDIR + "trail02","southwest");
}

int
drink_fun(string str)
{
   notify_fail("Drink from what? The stream?\n");
   if (!strlen(str) || !parse_command(str, ({ }), "[water] [from] [the] 'stream'"))
       return 0;
      
   if(TP->drink_soft(2500, 1))
      TP->drink_soft(2500);
   else if(TP->drink_soft(750, 1))
      TP->drink_soft(750);
   else if(TP->drink_soft(500, 1))
      TP->drink_soft(500);
   else if(TP->drink_soft(100, 1))
      TP->drink_soft(100);
   else
   {
      write("You can't drink any more, you're stuffed!\n");
      say(QCTNAME(TP) + " tries to drink from the" +
         " stream, but fails.\n");
      return 1;
   }
   write("You lean over the bridge to drink some water.\n");
   say(QCTNAME(TP) + " leans over the bridge to "+
     "drink some water.\n");
   return 1;
}
void
init()
{
   ::init();
   add_action("drink_fun" , "drink");
}