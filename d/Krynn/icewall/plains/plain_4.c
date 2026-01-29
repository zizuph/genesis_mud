/* Created by Stevenson */
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
inherit ICEOUTROOM;

create_icewall_room() {
   set_short("Village Entrance");
   set_long(
      "You stand before the entrance to a small village. Voices "
      + "drift towards you but you cannot make out what is "
      + "being said. The glacier is back the way you came. "
      + "\n");
   
   add_item("glacier", "You see it to the south.\n");
   add_cmd_item(({"voices", "to voices"}), "listen",
      "You hear: Qejbiu bla oierul bla bla bla.\n");
   add_item("village","It is a small village that Macker should "
      + "create a better descriptioni for (*wink*).\n");
   
   add_exit(ICE_PLAINS+"plain_3","southeast");
	add_exit(ICE_PLAINS+"village/village_1","north");
}

int closed() {
   write("Area closed until Macker fixes it up good and proper.\n");
   return 1;
}
