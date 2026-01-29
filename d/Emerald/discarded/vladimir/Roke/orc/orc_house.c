/* Vladimir 7-26-94 */
inherit "/std/room.c";
#include <macros.h>
#include "/sys/stdproperties.h"
#include "local.h"
#define TO this_object()
string long;
object skeez;

create_room()
{
   set_short("An orc family's home");
   set_long("You have entered the home of a particularly dirty orc family.\n" 
      + "The idea of calling this place home makes you cringe slightly.\n" 
      + "Strewn about the room are various objects of little value\n" 
      + "to you. In the northeast corner of this house is a small\n" 
      + "rotting table with two chairs of equal conditions sitting\n" 
      + "around it. There is a small wood stove in the middle of the\n" 
      + "room. There are three crude orc beds lined up against the\n"
      + "wall. There is a window over the beds square in shape.\n");
   add_item(({"wood stove", "stove", "furnace"}),
      break_string("This a medium sized stove that is design to keep the "+
         "occupants of the house warm. From the looks and feel "+
         "of the house, it seems the stove does not work well, "+
         "if it works at all.\n", 70));
   add_item(({"table", "small table", "wooden table"}),
      break_string("This small table is made from rotten wood. It seems "+
         "like it could hardly hold the slightest item on it. "+
         "You can see the letters V and M carved side by side "+
         "into the table.\n", 70));
   add_item(({"chair", "chairs", "seat"}),
      break_string("This chair probably could not support it's own weight "+
         "if it were not leaning agianst the wall.\n", 70));
   add_item(({"bed", "beds", "orc bed", "orc beds"}),
      break_string("These beds look very uncomfortable as well as smelly. "+
         "The fabric on the beds looks and feels like burlap. "+
         "Needless to say you do not plan on spending the night "+
         "here.\n", 70));
   add_item(({"window", "square window", "small window", "small square window"}),
      break_string("As you look out the window you realize how warm and "+
         "clean the outside world is compared to this place. "+
         "Even Sparkle with it's rats and mice is better than "+
         "being here.\n", 70));
   add_prop(ROOM_I_INSIDE, 1);
   add_exit("/d/Genesis/start/human/wild2/orc_sett", "west");
   reset_room();
}
reset_room()
{ 
   if(!skeez)
      {
      skeez = clone_object(ORC+"monsters/skeezle");
      skeez->move_living("xxx", TO);
   }
}
