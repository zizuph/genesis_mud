inherit "/d/Emerald/telberin/arm/w_mithril_base";

#include <wa_types.h>
#include <stdproperties.h>

void create_mithril_armour()
{
  set_name("bracers");
  set_pname("bracers");
  set_short("white-mithril bracers");
  set_pshort("white-mithril bracers");
  set_long("An exquisite pair of white-mithril bracers.\n");
  set_ac(40);
  set_at(A_ARMS);

  add_prop(OBJ_I_VALUE, 3800);
  add_prop(OBJ_I_WEIGHT, 4000);
  add_prop(OBJ_I_VOLUME, 3000);
}
