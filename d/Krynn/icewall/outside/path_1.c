#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
inherit ICEOUTROOM;

create_icewall_room() {
   set_short("A wide path");
   set_long(
      "Immediately in front of you is a path leading to the "
      + "Plains of Icewall. Nearly buried by snow you can see "
      + "the top edge of a sign which points northwest."
      + "\n");
   
   add_item("plains","This path will reach them eventually.\n");
   add_item("snow","It is what makes Icewall so white.\n");
   add_item("path","It is wide and well-used.\n");
   
   add_item("sign","It is buried in snow.  Maybe you can brush "
      + "some of it off?\n");
   
   add_cmd_item(({"snow","sign"}),"brush",
      "You brush away the snow and see a sign:\n\n"
      + "          ------------------\n"
      + "         (      WARNING:    )\n"
      + "          )                  )\n"
      + "          (     DRAGONS!!!  (\n"
      + "           -----------------\n"
      + "                   ||\n"
      + "                   ||\n\n");
   
   add_cmd_item("sign","read","It is buried in snow. Brush it off maybe?\n");
   add_exit(ICE_OUT+"path_2","northwest");
   add_exit(ICE_OUT+"bottom_of_ice","east");
}
