/* Created by Stevenson */
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
inherit ICEOUTROOM;

create_icewall_room() {
   set_short("Plateau");
   set_long(
      "You find yourself on a small plateau overlooking the "
      + "rest of the plains. North of you are some trailing wisps "
      + "of smoke. East you can see movement. "
      + "\n");
   
   add_item("plateau","You're standing on it.\n");
   add_item(({"smoke","wisps"}),"You cannot make out the source.\n");
   add_item("movement","Strange shapes are moving about in the "
      + "the distance.\n");
   
   add_exit(ICE_PLAINS+"plain_2","south");
   add_exit(ICE_PLAINS+"plain_4","northwest");
   add_exit(ICE_PLAINS+"plain_5","east");
}
