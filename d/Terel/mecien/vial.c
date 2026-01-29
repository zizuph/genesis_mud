inherit "/std/object";
#include <stdproperties.h>

create_object()
{
    set_name("vial");
    set_adj("crystal");
  set_long("A beautiful cut-crystal vial. It is etched with a\n"
  + "simple four-pointed star.\nIt is empty.\n");
  add_name("mystic_vial");
    add_prop(OBJ_I_VALUE, 100);
}

