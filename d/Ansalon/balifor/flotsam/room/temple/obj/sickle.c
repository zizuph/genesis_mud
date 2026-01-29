inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

create_weapon()
{
   set_name("sickle");
   set_adj("golden"); 
   set_short("golden sickle");   set_long("This weapon consists of a golden semi-" +
      "circular blade attached to a blackened wooden " +
      "handle. Upon the handle a symbol of a goats " +
      "skull has been burned upon it. \n");
   set_default_weapon(18,15,W_KNIFE,W_SLASH | W_IMPALE, W_ANYH);
   add_prop(OBJ_I_VOLUME, 360);
   add_prop(OBJ_I_WEIGHT, 350);
}

