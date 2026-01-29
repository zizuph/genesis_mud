/* Created by Stevenson */
/* Created by Stevenson */
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
inherit ICEOUTROOM;

object penguin;

reset_icewall_room() {
   if (!penguin) {
      penguin = clone_object(ICE_CAST_M+"penguin");
      penguin->move(TO);
   }
}

create_icewall_room() {
   set_short("High in Plains");
   set_long(
      "You feel a strange set of eyes on you.\nYou are quite high "
      + "on the glacier right now. It begins to slope downward to the "
      + "east where you can hear occasional splashing sounds. Back west "
      + "is a plateau overlooking much of the glacier. "
      + "\n");
   
   add_item("glacier","The glacier is ancient and predates the Cataclysm.\n");
   add_item("eyes","You don't know who they belong to but "
      + "they make you very nervous.\n");
   add_item("plateau","It is to the west of you.\n");
   
   add_exit(ICE_PLAINS+"plain_3","west");
   add_exit(ICE_PLAINS+"plain_6","south");
   add_exit(ICE_PLAINS+"plain_7","east");
   
   reset_icewall_room();
}
