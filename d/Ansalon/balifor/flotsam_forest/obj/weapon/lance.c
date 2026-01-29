inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

create_weapon()
{
   set_name("lance");
   set_adj("steel");
   add_adj("great");
   set_short("great steel lance");
   set_pshort("great steel lances");
   set_long("This long steel weapon is of impressive make. You " +
      "would imagine it would be carried by a skilled warrior " +
      "on at least a heavy warhorse.\n");
   set_default_weapon(32,26,W_POLEARM,W_IMPALE,W_BOTH);
   add_prop(OBJ_I_VOLUME, 2000);
   add_prop(OBJ_I_WEIGHT, 10000);
}
