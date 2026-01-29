/* Created by Stevenson */
/* Created by Stevenson */
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
   set_short("on the icy plains");
   set_long(
      "You are on the frozen plains of Icewall. There is "
      + "a peculiar sense of quiet in the area. You wonder "
      + "what life could possibly survive in this harsh "
      + "climate. Around you to the north and the east are "
      + "very high, snowcapped mountains."
      + "\n");
   
   add_exit(ICE_PLAINS+"plain_5","north");
   add_exit(ICE_PLAINS+"plain_8","northeast");
   
   reset_icewall_room();
}
