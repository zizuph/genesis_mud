inherit "/std/room";

#include "default.h"

inherit CASTLE_ROOM;


void
create_room()
{
   set_short("Metal passage");
   set_long("This passage is strange, it is metal lined. There is stone "+
      "beneath the metal jacket, but the metal is fairly thick. The passage "+
      "takes a sharp turn here, leading northwest and west.\n");

   add_exit(CASTLE_DIR + "3k11","northwest",0);
   add_exit(CASTLE_DIR + "3k13","west",0);
   
   add_item(({"passage","metal"}),"The metal is nice and shiny, but cold.\n");
   
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_NO_ATTACK, 1);
   add_prop(ROOM_I_LIGHT, 0);
}
