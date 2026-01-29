inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

create_weapon()
{
   set_name("knife");
   set_adj("goblin"); 
   set_short("goblin knife");   set_long("This short, notched knife of shoddy workmanship " +
      "is a weapon commonly used by goblin warriors too weak " +
      "to wield a club. \n");
   set_default_weapon(12,12,W_KNIFE,W_SLASH | W_IMPALE, W_ANYH);
   add_prop(OBJ_I_VOLUME, 360);
   add_prop(OBJ_I_WEIGHT, 350);
}

