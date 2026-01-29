inherit "/d/Emerald/telberin/arm/w_mithril_base";

#include <wa_types.h>
#include <stdproperties.h>

void create_mithril_armour()
{
  set_name("greaves");
  set_pname("greaves");
  set_short("white-mithril greaves");
  set_pshort("while-mithril greaves");
  set_long("A finely crafted pair of greaves fashioned from " +
      "white mithril.\n");
  set_ac(42);
  set_at(A_LEGS);

  add_prop(OBJ_I_VALUE, 3000);
  add_prop(OBJ_I_WEIGHT, 6000);
  add_prop(OBJ_I_VOLUME, 4500);
}
