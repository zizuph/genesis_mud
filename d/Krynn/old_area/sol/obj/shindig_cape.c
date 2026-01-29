inherit "/std/armour";
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>

void
create_armour()
{
   set_name("cape");
   set_ac(3);
   set_at(A_ROBE);
   set_short("bright red flamboyent cape");
   add_adj(({"bright","red","flamboyent"}));
   set_long("This is a bright red tunic, very flamboyent in both "+
      "decoration and colour. The cape is connected with a "+
      "bright golden brooch with the initials SL engraved in "+
      "it. It is rather small, apparently worn by kender or "+
      "gnomes.\n");
   add_prop(OBJ_I_VOLUME, 4750);
   add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(3, A_ROBE));
   add_prop(OBJ_I_VALUE, 1000);
}

