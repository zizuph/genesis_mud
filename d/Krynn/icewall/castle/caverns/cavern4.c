/*Created by Stevenson*/
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
inherit ICEINROOM;

create_icewall_room()
{
   set_short("Rainbow Room");
   set_long(BS(
         "You have stumbled into a high-ceilinged cavern of breath-taking "
         + "beauty.  All about you are wondrous rainbows of light flashing on the ice. "
         + "You notice that you are standing upon what appears "
         + "to be an icy pavement leading off to the east..."
         ,65));
   
   add_item("ceiling","It stretches very high above you.\n");
   add_item(({"rainbow","rainbows"}),"They flicker and flash from "
      + "the ice dazzling you with their colorful wonder.\n");
   add_item("ice","Everything you see is covered in a thin sheen of ice.\n");
   add_item("pavement","It is actually a thick and flat partition of ice "
      + "which has collected on the ground over the centuries.\n");
   add_item("ground","You see an icy pavement leading off to the east.\n");
   
   add_exit(CAVE+"cavern1.c","west");
add_exit(QUEST+"dryland","east");
}
