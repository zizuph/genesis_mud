inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>

void create_armour()
{
  set_name("ring");
  set_adj("emerald");
  set_at(A_ANY_FINGER);
  set_ac(5);
  set_long("An emerald ring; its band seems to be made of mithril, " +
      "and the gem is truly enormous.\n");

  add_prop(OBJ_I_VALUE, 500);
  add_prop(OBJ_I_WEIGHT, 100);
  add_prop(OBJ_I_VOLUME, 50);
}
