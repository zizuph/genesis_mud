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
    set_name("fauchard");
    add_name(({"polearm"}));
    set_adj("well-made");
    add_adj(({ "Rohirrim", "ash" }));
    set_short("fauchard"); 
    set_long(BSN("A blade, both sharply pointed and having a cutting "+
    "edge, is attached to a long ash shaft."));

    set_default_weapon(23, 30, W_POLEARM, W_IMPALE | W_SLASH, W_BOTH, 0);
    
    add_prop(GONDOR_M_ROHIRRIM_NO_SELL, 1);
    add_prop(OBJ_I_VOLUME, 2500);  
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(23,30)+random(100)-50);
}
