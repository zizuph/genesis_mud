/* Vladimir 8-09-94 */
inherit "/std/room.c";
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "local.h"
#define TO this_object()

string long;
object orc, orc1, orc2;
create_room()

{
   set_short("Orc guardroom");
   set_long(
      "This is a crudely built room that is carved from stone that\n"
      + "lies around the fortress. There are four holes in the wall that\n"
      + "you think are suppose to be arrow slits that vary in levels. In\n"
      + "the middle of this dank room sits a small stone table.\n");
   add_item(({"slits", "arrow slits", "holes"}),
      break_string("These slits are spread at various levels along "+
         "three of the four walls.\n", 70));
   
   add_item(({"table", "stone table", "small table", "small stone table"}),
      break_string("This is a small stone table. It has a very rough "+
         "surface and seems uneven.\n", 70));
   add_prop(ROOM_I_INSIDE, 1);
   add_exit(ORC+"hall3", "south");
   reset_room();
   
}

reset_room()
{
   if(!orc)
      {
      orc = clone_object(ORC+"monsters/orc1");
      orc-> move_living("xxx", TO);
   }
   if(!orc1)
      {
     orc1 = clone_object("/d/Genesis/start/human/obj/orc");
      orc1->move_living("xxx", TO);
   }
   if(!orc2)
      {
      orc2 = clone_object("/d/Genesis/start/human/obj/orc");
      orc2->move_living("xxx", TO);
   }
}

