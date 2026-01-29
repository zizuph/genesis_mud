/*Created by Stevenson*/
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
inherit ICEINROOM;

create_icewall_room() {
   set_short("Mural Chamber");
   set_long(BS(
         "You are in a chamber whose walls are covered in murals. A "
         + "soft light seems to emanate from the east while "
         + "soft tendrils of frozen mist seep from the passage "
         + "to the northwest. "
         ,65));
   
   add_item("passage","It runs both northwest and east from here.\n");
   add_item("walls","They are smooth and worn from time.\n");
   add_item("murals","The murals depict battle scenes in "
      + "which valiant knights astride silver "
      + "and golden dragons are battling the evil forces of "
      + "Takhisis. One such knight has impaled an evil red dragon "
      + "with his dragonlance.\n");
   add_item(({"knight","knights","dragon","dragonlance",
            "gold dragon","silver dragon","lance"}),
      "The murals are covering the walls and depict battles of Good "
      + "versus Evil.\n");
   add_item("mist","The mist is very cold to the touch.\n");
   add_cmd_item("mist","touch","You shiver at the touch.\n");
   add_item("light","You cannot discern its source.\n");
   add_exit(QUEST+"to_drag_2","northwest");
   add_exit(QUEST+"iceblock","east");
}
