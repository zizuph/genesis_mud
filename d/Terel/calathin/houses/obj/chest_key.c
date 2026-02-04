inherit "/std/key";

#include <stdproperties.h>

create_key()
{
  set_adj("small");
  add_adj("iron");
  set_long("A small, iron key.\n");
  add_name("tomas:chest_key");
  add_prop(OBJ_M_NO_BUY,1);
}
