inherit "/std/receptacle";
inherit "/lib/store_support";

#include <stdproperties.h>

void
create_container()
{
  set_name("flask");
  set_adj("glass");
  set_adj("empty");
  add_name("shaman_flask");

  set_short("empty glass flask");
  set_long(break_string("This is an empty glass flask in which "+
    "shaman uses to make their potions in.\n", 60));

  add_prop(CONT_I_WEIGHT,          50);
  add_prop(CONT_I_MAX_WEIGHT,      550);
  add_prop(CONT_I_VOLUME    ,      500);
  add_prop(CONT_I_MAX_VOLUME,      500);

  add_prop(OBJ_I_VALUE, 10);
}

void
init()
{
  ::init();
}