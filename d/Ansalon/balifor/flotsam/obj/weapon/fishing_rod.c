inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

create_weapon()
{
   set_name(({"rod", "fishing rod", "_flotsam_f_rod_"}));
   set_adj("fishing");
   set_short("fishing rod");
   set_pshort("fishing rods");
   set_long("This is a small battered fishing rod with a line " +
      "and a hook. \n");
   set_default_weapon(5,5,W_POLEARM,W_IMPALE,W_BOTH);
   add_prop("mystic_weapon", 1);
   add_prop(OBJ_I_VOLUME, 500);
   add_prop(OBJ_I_WEIGHT, 500);
}
