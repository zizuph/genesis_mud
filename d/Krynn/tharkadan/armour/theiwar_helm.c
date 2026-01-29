/* Dwarven helm. */

inherit "/std/armour";
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"

void
create_armour()
{
   set_name("helmet");
   set_ac(35);
   set_at(A_HEAD);
   set_am( ({ -2, 3, 0 }) );
   set_adj("dark");
   set_adj("dwarf");
   set_short("dark dwarf helmet");
   set_long("This is a helmet of fine steel in the style of the dark " +
       "dwarves of the Theiwar clan.\n");
   add_prop(OBJ_I_VOLUME, 3000);
   add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(35, A_HEAD));
   add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(35));

   set_af(TO);

}

