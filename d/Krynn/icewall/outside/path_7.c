#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
inherit ICEOUTROOM;

create_icewall_room() {
   set_short("edge of Plains");
   set_long(
      "You stand at the edge of a large glacier which marks the "
      + "beginning of the plains of Icewall. You can see smoke "
      + "rising into the air off to the northeast and a very "
      + "harsh wind is whipping up a treacherous looking storm "
      + "far to the east. "
      + "\n");
   
   add_item("snow","It makes Icewall white.\n");
   add_item("plains","They are north of here somewhere.\n");
   add_item(({"glacier","plains"}),"The plains actually rest on the "
      + "surface of a glacier. In fact, this glacier predates the "
      + "cataclysm which changed the face of Krynn.\n");
	add_item("smoke", "It is a normal thin stream of smoke rising" +
		" up into the sky from a single source. It looks like " +
		"it could be from a campfire or a chimney.\n");
   add_item("wind","The wind is stirring up stinging particles of ice "
      + "snow that could easily rip your skin off.\n");
   add_item("storm","I wouldn't venture into it without some form of "
      + "protection if I were you.\n");
   add_exit(ICE_PLAINS+"plain_1","southeast");
   add_exit(ICE_OUT+"path_6","southwest");
}
