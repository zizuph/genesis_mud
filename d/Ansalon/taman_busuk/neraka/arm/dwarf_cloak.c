inherit "/std/armour";
inherit "/lib/keep";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

void
create_armour()
{
   set_name("cloak");
   add_adj("red");
   add_adj("gold-lined");
   set_short("red gold-lined cloak");
   set_long("You marvel at softness of this cloak. The insides are lined "+
   "with smooth satin. Gold designs adorn the fringes of this cloak.\n");
   set_ac(6);
   set_at(A_ROBE);
   add_prop(OBJ_I_VALUE,100);
   add_prop(OBJ_I_VOLUME, 800);
   add_prop(OBJ_I_WEIGHT, 1000);
}
