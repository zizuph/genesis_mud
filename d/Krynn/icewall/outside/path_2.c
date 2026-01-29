#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
inherit ICEOUTROOM;

create_icewall_room() {
   set_short("Wide, twisty path");
   set_long(
      "You are on a twisty path which leads to the plains. "
      + "Because of the wind, your visibility is almost gone. "
      + "Somehow, you sense that you are not alone."
      + "\n");
   
   add_item("snow","It makes Icewall white.\n");
   add_item("plains","They are north of here somewhere.\n");
   add_item("path","It is wide and twisty here.\n");
   add_exit(ICE_OUT+"path_1","southeast");
   add_exit(ICE_OUT + "path_3","northeast");
}
