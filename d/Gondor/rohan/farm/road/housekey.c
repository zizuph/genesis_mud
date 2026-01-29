inherit "/std/key";
#include "/sys/stdproperties.h"

create_key()
{
  ::create_key();
  set_adj("iron");
  set_pshort("iron keys");
  set_long("This is a large iron key.\n");
  set_key("Cottage_Key");
  add_prop(OBJ_I_VOLUME,10);
  add_prop(OBJ_I_WEIGHT,10);
  add_prop(OBJ_I_VALUE,10);
}

