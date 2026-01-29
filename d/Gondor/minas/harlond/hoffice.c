/*
 * 28-sep-1993, Olorin
 * office of the harbour master at the harlond
 */
inherit "/d/Gondor/common/room";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

object hmaster;

void
add_stuff()
{
   if (!objectp(hmaster))
   {
      hmaster=clone_object(MINAS_DIR + "npc/hmaster");
      hmaster->move(TO);
   }
}

void
create_room()
{
   set_short("the office of the Harbour Master");
   set_long(BSN(
         "You are in the offices of the Harbour Master of the Harlond "
         + "in Minas Tirith. There is a large desk here, and on the "
         + "walls you can see some nautical maps. To the southeast "
         + "the pier is visible through the only exit. "));
   
   add_item("desk","This desk is old and cluttered with maps of oceans.\n");
   add_item(({"map","maps"}), BSN(
         "These maps must map all of the known world by sea, but they "
     + "are unintelligible to you, not being a sailor."));
   add_item("pier","The pier stretches out into the water.\n");
   add_prop(ROOM_I_INSIDE,1);
   add_exit(MINAS_DIR+"harlond/pier4","southeast",0);
   add_stuff();
}

void
reset_room()
{
   add_stuff();
}

