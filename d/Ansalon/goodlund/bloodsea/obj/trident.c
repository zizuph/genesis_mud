inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

create_weapon()
{
   set_name("trident");
   set_adj("forked");
   set_short("forked trident");
   set_long("This long polearm is a three pronged trident, forged in the " +
     "water depths of the Bloodsea by the Dargonesti sea-elves. Sharp and " +
     "deadly, these weapons are used to drive off the great sharks and serpents " +
     "that hunt the seven seas.\n");
   set_default_weapon(39,35,W_POLEARM,W_IMPALE,W_BOTH);
   add_prop(OBJ_I_VOLUME, 5000);
   add_prop(OBJ_I_WEIGHT, 4500);
}
