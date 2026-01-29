/* Weapon coded by Arren */ 
inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>

#include "/d/Gondor/defs.h"

void
create_weapon()
{
    set_name("halberd");
    add_name("polearm");
    set_pname("halberds");
    add_pname("polearms");
    set_adj("steel-edged");
    add_adj("orc");
    set_short("steel-edged halberd");
    set_pshort("steel-edged halberds");
    set_long(BSN(
        "The head of this halberd is blackened beyond polishing, "
      + "but the balance of the halberd seems to be fine. "
      + "Welded to the axe blade is a steel edge."));

    set_default_weapon(26, 38, W_POLEARM, W_IMPALE | W_SLASH, W_BOTH, 0);
    
    add_prop(OBJ_I_VOLUME, 1600);  
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(26,38) + random(150) - 75);
}
