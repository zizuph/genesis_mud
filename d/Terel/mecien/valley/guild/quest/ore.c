/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/object";
#include <stdproperties.h>

create_object()
{
   set_name("ore");
   add_adj("meteorite");
   set_adj("fragment of");
  add_name("meteorite ore");
  set_long("A small fragment of some metal, seemingly cosmic in\n"
    + "its origin. It is silvery-gray, yet sprakles prismatically.\n");
   add_name("mystic_quest_ore");
   add_prop(OBJ_I_VALUE, 85);
}

