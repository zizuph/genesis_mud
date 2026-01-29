inherit "/d/Shire/common/lib/room";

#include "/d/Shire/common/defs.h"
#include <stdproperties.h>

object hum;

create_room()
{
   set_short("A human's house in Bree");
   set_long("You are inside a small house. Everything in here is "
      +"totally messy. It is slovenly and it is easy to see that "
      +"the human dwelling inside is fond of making messes. There is a "
      +"bookshelf standing against one wall, but there are few "
      +"books left there. There is a desk in one corner and a chair is behind "
      +"it. The fireplace on the wall is devoid of fire.\n");
   
   add_item(({"book shelf","bookshelf","shelf"}),
      "The bookshelf is filled with books. It is made of pine and looks "
      +"sturdy.\n");
   
   add_item("books","There are lots of different books here. One book you notice "
      +"has the title 'Planting a proper garden'. Various other "
      +"books are also there. There are many books about trees and gardens "
      +"and that is not surprising when you think of what hobbits are most "
      +"fond of. Gardens, plants, trees and herbs.\n");
   
   add_item("wall","The wall looks strong, compared with how it look from the outside "
      +"you can clearly see this cabin is much stronger then what it "
      +"appears to be.\n");
   
   add_item("desk","The desk has some drawers in it, not unusual for a desk to have. "
      +"It looks very old, and the wood it is made from looks like oak.  "
      +"Oak is a very common wood to make desks and chairs from.\n");
   
   add_item("chair","This is a wooden chair, made of pine. It is small of size, fitting "
      +"to the desk.\n");
   
   
   add_item(({"fire","fireplace"}),"The fireplace looks almost "
      +"completely unused. That seems odd as most "
      +"Bree inhabitants keep a fire burning most "
      +"of the time to ward off the cold.\n");
   
   add_prop(ROOM_I_INSIDE,1);
   
   add_exit(ROAD_DIR +"broad05","out",0,2);
   
   reset_room();  
}

reset_room()
{ 
   if (!hum)
      {
      hum = clone_object(BREE_DIR + "npc/" + "bhuman");
      hum->move(TO);
   }
}
init()
{
   ::init();
   add_action("do_push","push");
}

int
do_push(string str)
{
  if (!str)
  {
     notify_fail("Push what?\n");
     return 0;
  }
   if (str != "bookshelf")
      {
      NF("You push the "+str+", but nothing happens.\n");
      return 0;
   }
   /*    if(present(hum))
      *      {
      *      write("The human won't let you near the bookshelf.\n");
      *      return 0;
      *      }
   */
   
   say(QCTNAME(TP) + " falls down into a hole!\n");
   write("You push the bookshelf and discover it is a trap!\n");
   write("You fall down into a dark hole.\n");
   TP->move_living("M","/d/Shire/common/bree/cellar1",1);
   
   return 1;
   
}
