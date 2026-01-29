#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
inherit ICEOUTROOM;

create_icewall_room() {
set_short("A cold, windy path");
   set_long(
      "You are halfway along the icy path.  A chill wind is "
      + "blowing from the east, causing you to shiver.  You "
      + "hope that there is warmth somewhere nearby. "
      + "\n");
   
   add_exit(ICE_OUT+"grif_1","down");
add_item("path","It is narrow and twisted.\n");
add_item("ice", "It is purple and very warm- NOT. What do you think " +
		"ice looks like? Ok, I'll explain. The ice is pure white. It is also very hard and very cold. Happy??\n");
}
