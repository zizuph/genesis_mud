/****************************************/
/* Main Entrance Hall of Icewall Castle */
/*   Floor 2*/
/* Coded by Steve*/
/* fixed up by Stevenson */
/****************************************/

#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>

inherit ICEINROOM;

object husky;
string str;

create_icewall_room()
{
   set_short("Main Hall of Second Floor");
   set_long(BS(
         "\nYou are standing at the top of the stairs on the second"
         + " floor of the castle. A giant grandfather clock sits majestically"
         + " against the wall and a ticking sound echoes around the room."
         + " There is a plaque pinned to one of the walls." +
         " Dimly lit halls lead to other parts of the second floor."
         +"",75));
   
   
   add_item(({"clock","grandfather clock","grandfather"}),
      "The huge clock is made out of solid oak and its sound echoes\n"
      + "through the hallway.\n");
   add_item("plaque",
      "The plaque has something written on it.\n");
   add_item(({"halls","hallways"}),
      "They lead off to other parts of the second floor.\n");
   
   add_exit(ICE_CAST2_R + "hall2_2.c", "north");
   add_exit(ICE_CAST2_R + "hall1_2.c", "east");
   add_exit(ICE_CAST2_R + "storage.c", "west");
   add_exit(ICE_CAST1_R + "main_hall.c", "down");
   
   reset_icewall_room();
}

init()
{
   ::init();
   add_action("read_plaque","read");
}

read_plaque(str)
{
   if (str != "plaque")
      {
      NF("Read what?\n");
      return 0;
   }
   else
      {
      write(
         "\n                Ice Battle of 3060\n"
         + "      Death is the only means of survival\n\n");
      
      return 1;
   }
}

reset_icewall_room()
{
   if (!husky)
      {
      husky = clone_object(ICE_CAST_M + "husky2.c");
      husky->move_living("xxx", TO);
   }
}
