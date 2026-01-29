inherit "/std/room.c";

#include <macros.h>
#include "/sys/stdproperties.h"
#include "local.h"
#define TO this_object()
#define TP this_player()
string long;
object figure;

create_room()
{
   set_short("Musty room");
   set_long("This is an extremely musty and smelly room. It looks\n"
      + "oddly empty. You can crawl back through the small hole \n"
      + "in the wall from which you came.\n");

   add_item(({"hole in the wall", "hole"}),
              "It seems quite small.\n");
   add_item(({"stones", "stone"}), "They are all cut the wrong way, "+
              "and are the incorrect size.\n");
   add_prop(ROOM_I_LIGHT, -2);
   add_prop(ROOM_I_INSIDE,1);


  add_item("hole",
    "A small hole that looks just large enough to crawl through.\n");

add_cmd_item(({"northwest", "hole"}), "enter", "@@enter");
  add_cmd_item("hole","enter","@@enter");

  reset_room();
}
reset_room()
{
 if(!figure)
  {
  figure = clone_object(ORC+"obj/genfigure");
  figure->add_prop(OBJ_I_HIDE, 20);
  figure->move(TO);
  }
}


enter()
{
  write("You just manage to squeeze through the hole. It is a good\n"+
        "thing that you are not clostrophobic, or are you?\n");
  set_dircmd("hole");
TP->move_living("through the hole", ORC+"r5");
     return "Aahh! It feels good to stand up again!\n";
}





 
