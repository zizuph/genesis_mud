
inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>

void
create_armour()
{
  set_name("robe");
  set_short("dark swaddling robe");
  add_adj(({"swaddling", "dark"}));
  set_long("These robes are made of a heavy dark "
          +"cloth of great age.\nThey smell of the dead.\n");
  set_ac(1);
  set_at(A_ROBE);

  add_prop(OBJ_I_VALUE, 70);
  add_prop(OBJ_I_VOLUME, 200);
  add_prop(OBJ_I_WEIGHT, 100);
}
