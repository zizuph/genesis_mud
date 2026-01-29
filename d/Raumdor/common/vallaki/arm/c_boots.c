/*     Created by:      ???
 *     Location:        
 *     Modified:        Toby, 970919 (fixed pluralform)
 */

inherit "/std/armour";
#include "/d/Raumdor/defs.h"

void
create_armour()
{
    ::create_armour();
    set_name("pair boots");
    add_name("boots");
    set_adj("leather");
    set_short("pair of leather boots");
    set_pshort("pairs of leather boots");
    set_long("These are a nice pair of dusty leather boots.\n");
    set_at(A_FEET);
    set_ac(1);
    add_prop(OBJ_I_WEIGHT,500);
    add_prop(OBJ_I_VOLUME,300);
    add_prop(OBJ_I_VALUE,30+random(10));
}

