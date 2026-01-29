inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>
#include <language.h>
#include <macros.h>

create_weapon()
{
   set_name(({"broadsword", "sword"}));
   set_short("chipped broadsword");
   set_adj("chipped");
    add_adj("metal");  /* added by Gorboth, July 2007 */

   set_pshort("chipped broadswords");
   set_long("This once-beautiful broadsword has a chipped blade. " +
            "However, that probably affects the effectiveness little. " + 
            "It has a simple hilt and pommel to match the now-simple " +
            "blade.\n");
   set_default_weapon(25, 32, W_SWORD, W_SLASH | W_IMPALE, W_ANYH);
   add_prop(OBJ_I_VOLUME, 1600);
   add_prop(OBJ_I_WEIGHT, 5000);
   add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(25,32));
}


