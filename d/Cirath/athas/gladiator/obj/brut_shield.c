inherit "/std/armour";
#include "../defs.h"
#include <std.h>
#include <stdproperties.h>
#include <wa_types.h>

create_armour()
{
   set_name("shield");
   set_adj("mekillot");
   add_adj("large");
   set_short("large mekillot shield");
   set_long("This shield is nearly five feet tall and "
   	+"made from a piece of mekillot chitin.  Swirled "
   	+"with black and brown, the shield almost seems to "
   	+"absorb light.  After examining the inside of the "
   	+"shield, you notice it is weighted with blocks of "
   	+"stone to help absorb impact.  This makes it very "
   	+"heavy .\n");
   set_ac(30);
   set_at(A_SHIELD);
   add_prop(OBJ_I_WEIGHT,12000);
   add_prop(OBJ_I_VOLUME,5000);
}
