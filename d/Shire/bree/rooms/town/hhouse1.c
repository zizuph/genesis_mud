/*
 * Updated entrance to Tricksters guild
 * Finwe, June 2002
 * Changed the long description from "few" books to "many" books
 * so it matches the add_items.
 * Raymundo, June 2021 
  */
 
#include "/d/Shire/sys/defs.h"
#include "defs.h"
#include <stdproperties.h>

inherit "/d/Shire/common/lib/room";

object hum;

create_room()
{
   set_short("A human house in Bree");
   set_long("You are inside a small house. Everything in here is "
      +"totally messy. It is slovenly and it is easy to see that "
      +"the human dwelling inside is fond of making messes. There is a "
      +"bookshelf standing against one wall with many "
      +"books left there. There is a desk in one corner and a chair is behind "
      +"it. The fireplace on the wall is devoid of fire.\n");
   
   add_item(({"book shelf","bookshelf","shelf"}),
      "The bookshelf is filled with books. It is made of pine and " +
      "looks sturdy.\n");
   
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
   
        add_exit(ROAD_DIR + "broad05", "out", 0,0,1);
        add_exit(ROAD_DIR + "broad05", "east");

   reset_room();
}

reset_room()
{
   if (!hum)
      {
      hum = clone_object(NPC_DIR + "bhuman");
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
   
   say("The bookshelf swings open silently.\n");
   say(QCTNAME(TP) + " enters a the bookshelf.\n");
   say ("The bookshelf closes.\n");
   write("A bookshelf swings out from the wall.\n");
   write("You enter the bookshelf and disappear.\n");
   TP->move_living("M","/d/Shire/bree/rooms/town/backroom",1);
   
   return 1;
   
}
