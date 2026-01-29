#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
inherit ICEOUTROOM;

create_icewall_room() {
   set_short("Approaching the Plains");
   set_long(
      "To the east the Icewall Plains are very close, and "
      + "to the west you can see the path continuing. "
      + "\n");
   
   add_item("snow","It makes Icewall white.\n");
   add_item("plains","They are north of here somewhere.\n");
   add_item("path","It is covered with patches of slippery ice.\n");
   add_item("ice","The ice is covering the path in large, slippery patches.\n");
   add_exit(ICE_OUT+"path_5","west");
   add_exit(ICE_OUT + "path_7", "northeast");
}
