#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
inherit ICEOUTROOM;

void
load_min()
{
	(ICE_PLAINS + "plain_1.c")->load_me();
}


create_icewall_room() {
   set_short("View Point");
   set_long(
      "You are on a twisty path which leads to the plains. "
      + "The wind isn't too bad here and you can see your "
      + "surroundings a little better. To the north are mountains "
      + "and east you can see a large flat area which must "
      + "be the plains. "
      + "\n");
   
	set_alarm(2.0, 0.0, "load_min");
   add_item("snow","It is soft and beautiful.\n");
   add_item("mountains", "They are majestic and white.\n");
   add_item("plains","Off in the distance are the frozen plains.\n");
   add_item("path","It is wider here to accomodate more people.\n");
   
   add_exit(ICE_OUT+"path_5","northeast");
   add_exit(ICE_OUT+"path_3","south");
}
