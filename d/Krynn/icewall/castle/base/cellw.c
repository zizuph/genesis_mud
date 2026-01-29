#include "/d/Krynn/common/defs.h"
#include "/sys/stdproperties.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
inherit ICEINROOM;

object skeleton;

create_icewall_room()
{
   set_short("Prison cell");
   set_long(BS("You are in a prison cell. In the corner of the room are "
         +"a few brittle bones. The roof looks unsafe and may fall "
         +"at the slightest move.",70));
   
   add_item("bones",
      "The bones disintergrate at your touch.\n");
   add_item("cell",
      "The cell doors seem to be unlocked.\n");
   
   add_exit(BASE + "prisons","east",0);
   
   reset_icewall_room();
}

reset_icewall_room()
{
   if(!skeleton)
      {
      skeleton=clone_object(ICE_CAST_M+"skeleton");
      skeleton -> move_living ("xxx",TO);
   }
}
