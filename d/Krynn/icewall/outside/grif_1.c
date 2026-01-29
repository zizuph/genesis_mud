/* Created By Stevenson */
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
inherit ICEOUTROOM;

create_icewall_room() {
   set_short("Bottom of mountain");
   set_long(
      "You find yourself at the bottom of Icewall Mountain. "
      + "Around you are high snowbanks, and virtually no sign "
      + "of life. You wonder, with a shiver, if you too will "
      + "become part of the frozen scenery. "
      + "To the north you can make out what looks like a large "
      + "block of something. "
      + "\n");
   
   add_item("block","It is hard to tell with the the wind whipping up so much snow.\n");
   add_item(({"snow","banks","snowbanks","wind"}),
      "Apparently the wind is whipping the snow up into a frenzy.\n");
   add_item(({"mountain", "valley"}),
      "This entire valley is surrounded by mountains.\n");
   
   add_exit(ICE_OUT+"grif_2","up");
   add_exit(ICE_OUT+"bottom_of_ice","north");
}
