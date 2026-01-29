/* Ashlar, 3 Aug 97 */

inherit "/std/armour";
inherit "/lib/keep";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>

void
create_armour()
{
    set_name("belt");
    set_adj("leather"); 
    set_short("leather belt");    set_long("It is a belt made of thick leather, with two larger " +
        "rectangular pieces of leather attached to it. It is " +
        "unusually long.\n");
   set_ac(4);
   set_at(A_WAIST);
   add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(4)+random(10));
   add_prop(OBJ_I_VOLUME, 1500);
   add_prop(OBJ_I_WEIGHT, 3200);
}
