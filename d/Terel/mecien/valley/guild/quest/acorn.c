/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/object";
#include <stdproperties.h>

create_object()
{
   set_name("acorn");
   set_adj("large");
   set_long("It is a large acorn from an oak tree.\n");
   add_name("mystic_quest_acorn");
   add_prop(OBJ_I_VALUE, 1);
}

