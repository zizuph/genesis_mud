/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/object";
#include <stdproperties.h>

create_object()
{
   set_name("scroll");
   add_adj("ancient");
   add_name("mystic_quest_scroll");
   set_long("A very ancient scroll of vellum. It is marked with\n"
      + "cryptic symbols and writings.\n");
   add_cmd_item("scroll", "read", 
      "Neither the writings or the symbols seem to make any sense.\n");
   add_prop(OBJ_I_VALUE, 25);
}

