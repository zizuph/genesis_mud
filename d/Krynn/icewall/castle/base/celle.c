/* a prison cell - fixed up by Stevenson
* 
* in future put a skell here that you need to somehow resurrect
* for a quest.
*/

#include "/d/Krynn/common/defs.h"
#include "/sys/stdproperties.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
inherit ICEINROOM;

object door;

create_icewall_room()
{
   set_short("Prison cell");
   set_long(BS("You are in a prison cell. In the corner of the room is "
         +"a brittle skeleton. The roof looks unsafe and may fall "
         +"at the slightest move.",70));
   
   add_item("skeleton",
      "The skeleton disintegrates at your touch.\n");
   add_item("cell",
      "The cell doors seem to be unlocked.\n");
   add_item("roof","It looks as though it could fall "
      + "on your head and squash you like a grape.\n");
   
   door = clone_object(ICE_CAST_O + "celldoor1.c");
   door->move(TO);
   door->set_key(BASEKEY);
}
