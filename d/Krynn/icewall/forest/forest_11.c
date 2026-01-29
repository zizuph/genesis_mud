/*Created by Stevenson*/
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
inherit ICEOUTROOM;

object snowdrift;

reset_icewall_room() {
   if (!snowdrift) {
      snowdrift = clone_object(ICE_CAST_O+"snowdrift");
      snowdrift->move(TO);
   }
}

create_icewall_room() {
   set_short("Large Snowdrift");
   set_long(
      "There is a very fierce wind blowing snow around this "
      + "area in blinding intensity.  You find it difficult to stand "
      + "still against the raw fury of the elements. There is a rather large snowdrift here."
      + "\n");
   
   add_exit(ICE_FOREST+"forest_7","northwest");
   
   reset_icewall_room();
}

