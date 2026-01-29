/* Created by Stevenson */
/* Created by Stevenson */
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
inherit ICEOUTROOM;

init() {
   ADA("enter");
   ::init();
}

create_icewall_room() {
   set_short("Base of Mountain");
   set_long(
      "Before you, to the north, are the impressive "
      + "mountains which enclose Icewall. At the base of the "
      + "mountain is what appears to be a cave entrance. A strange salt-like smell seems to be emanating from it. "
      + "\n");
   
   add_item("mountains","They dwarf you in their size.\n");
   add_item("base","There appears to be a cave entrance in the base "
      + "of the northern mountains.\n");
   add_item("cave","A strange, salty smell emmanates from it.\n");
   add_item("smell","It is very salty.\n");
   add_item("entrance","It is in the northern mountains.\n");
   
   add_exit(ICE_PLAINS+"plain_5","west");
   add_exit(ICE_PLAINS+"plain_8","southeast");
}

int enter(string arg) {
   if (arg == "cave") {
      write("The smell of so much salt overcomes you and you feel "
         + "a little sick.\n");
      TP->reduce_hit_point(-5);
      if (TP->query_hp() < 1) TP->do_die();
      TP->move_living("into the cave",ICE_PLAINS+"sea",1,0);
      return 1;
   }
   NF("What?\n");
   return 0;
}
