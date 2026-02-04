/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/object";
#include <stdproperties.h>

create_object()
{
    set_name("vial");
    set_adj("crystal");
   add_name("empty_mystic_vial");
  set_long("A beautiful cut-crystal vial. It is etched with a\n"
  + "simple four-pointed star.\nIt is empty.\n");
  add_name("mystic_vial");
    add_prop(OBJ_I_VALUE, 100);
}

