inherit "/std/armour";

#include <stdproperties.h>
#include <wa_types.h>

void create_armour()
{
  set_name("robe");
  set_adj("dirty");
  add_adj("wool");
  set_long("An extremely dirty, wool robe; it smells strongly of " +
      "fresh dirt.\n");

  set_at(A_ROBE);
  set_ac(10);
  set_am(({ -2, 1, 1 }));

  add_prop(OBJ_I_VALUE, 50);
  add_prop(OBJ_I_VOLUME, 200);
  add_prop(OBJ_I_WEIGHT, 150);
}
