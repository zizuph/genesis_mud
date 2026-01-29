/*     Created by:      SARR 
 *     purpose:		
 *     Location:         
 *     Modified:        Toby, 97-09-18 (fixed plural name)
 */

inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"


void
create_armour()
{
    ::create_armour();
    set_name("pair of boots");
    set_pname("pairs of boots");
    add_name("boots");
    set_adj("steel-clad");
    add_adj("leather");
    set_short("pair of steel-clad leather boots");
    set_pshort("pairs of steel-clad leather boots");
    set_long("These are a pair of strong, leather boots. They are "+
    "steel enforced around the heel, toe and sole.\n");
    set_ac(3); 
    set_at(A_FEET);
    add_prop(OBJ_I_WEIGHT,120);
    add_prop(OBJ_I_VOLUME,100);
    add_prop(OBJ_I_VALUE,100+random(20));
}

