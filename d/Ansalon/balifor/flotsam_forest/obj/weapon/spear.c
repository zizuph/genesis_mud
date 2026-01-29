inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

create_weapon()
{
   set_name("spear");
   set_adj("hunting");
   set_short("hunting spear");
   set_pshort("hunting spears");
   set_long("This spear is typical of those used by hunters " +
      "of around the Goodlund forest areas. It consists of a " +
      "sharpened metal tip bound to a wooden staff, and is " +
      "decorated with tribal symbols.\n");
   set_default_weapon(24,18,W_POLEARM,W_IMPALE,W_ANYH);
   add_prop(OBJ_I_VOLUME, 2000);
   add_prop(OBJ_I_WEIGHT, 2500);
}
