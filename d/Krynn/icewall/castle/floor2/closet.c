/* Created by Macker & Stevenson */
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
inherit ICEINROOM;

object door, lens;

create_icewall_room()
{
   set_short("The closet of the master bedroom");
   set_long(BS(
         "This is the master bedroom closet.  There are, of course, all "
         + "kinds of clothes and shoes in here. It smells funny, but " +
         "you've smelled worse things. Still, it's not something " +
         "you'll get used to if you decide to stay in here for some strange " +
         "reason.\n"
         ,75));
   
   add_item("clothes", "They are old, wrinkled, and out of fashion.\n");
   add_item("shoes", "As you study the shoes a bit closer you discover " +
      "that they are the source of the funny smell which hangs in the air.\n");
   
   door = clone_object(ICE_CAST_O + "closetdoor1.c");
   door->move(TO);
   door->set_key(CLOSKEY);
   
   reset_icewall_room();
}

reset_icewall_room() {
   if (!lens) {
      lens=clone_object(ICE_CAST_O + "lens.c");
      lens->move(TO);
   }
}

