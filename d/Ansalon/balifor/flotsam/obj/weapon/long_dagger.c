inherit "/std/weapon";
inherit "/lib/keep";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

create_weapon()
{
   set_name("dagger");
   set_adj("nasty"); 
    add_adj("metal");  /* added by Gorboth, July 2007 */
   set_short("nasty dagger");   set_long("This is a nasty dagger, typically found " +
      "on shady characters, like assassins.\n");
   set_default_weapon(18,15,W_KNIFE,W_SLASH | W_IMPALE, W_ANYH);
   add_prop(OBJ_I_VOLUME, 360);
   add_prop(OBJ_I_WEIGHT, 350);
}

