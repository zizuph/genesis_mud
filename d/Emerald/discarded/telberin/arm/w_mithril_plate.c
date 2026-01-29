/* w_mithril_plate.c created by Shiva@Genesis
 * white mithril platemail.
 */ 
 
inherit "/d/Emerald/telberin/arm/w_mithril_base";

#include <wa_types.h>
#include <stdproperties.h>

void create_mithril_armour()
{
  set_name("plate");
  set_short("white-mithril plate");
  set_long("Beautifully crafted plate armour fashioned from " +
      "white mithril.\n");
  set_ac(47);
  set_at(A_BODY);

  add_prop(OBJ_I_VALUE, 4000);
  add_prop(OBJ_I_WEIGHT, 8000);
  add_prop(OBJ_I_VOLUME, 6000);
}
