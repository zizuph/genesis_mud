/* Weapon coded by Arren, April 94 */ 

inherit "/std/weapon";

#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/formulas.h"
#include "/d/Gondor/defs.h"

void
create_weapon()
{
    set_name("glaive");
    add_name(({"polearm"}));
    set_adj("well-used");
    add_adj(({ "Rohirrim", "ash" }));
    set_short("glaive"); 
    set_long(BSN("On the long ash shaft is fastened a single-edged cutting "+
    "blade."));

    set_default_weapon(21, 28, W_POLEARM, W_SLASH , W_BOTH, 0);
    
    add_prop(GONDOR_M_ROHIRRIM_NO_SELL, 1);
    add_prop(OBJ_I_VOLUME, 2300);  
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(21,28)+random(100)-50);
}
