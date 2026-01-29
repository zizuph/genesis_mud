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
    set_name("fork");
    add_name(({"polearm", "military-fork"}));
    set_adj("military");
    add_adj(({ "Rohirrim", "ash" }));
    set_short("military fork"); 
    set_long(BSN("Mounted on a long ash shaft is a two-pronged head, with "+
    "two backward pointing hooks."));

    set_default_weapon(22, 22, W_POLEARM, W_IMPALE , W_BOTH, 0);
    
    add_prop(GONDOR_M_ROHIRRIM_NO_SELL, 1);
    add_prop(OBJ_I_VOLUME, 2200);  
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(22,22)+random(100)-50);
}
