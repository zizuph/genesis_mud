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
    set_name("scimitar");
    add_name("sword");
    set_pname("scimitars");
    add_pname("swords");
    set_adj("dull");
    add_adj(({ "orc", "inferior" }));
    set_short("dull scimitar");
    set_pshort("dull scimitars");
    set_long(BSN("A curved sword with a single edge. The blade is dull "+
    "and the scimitar unbalanced. It's obviously of inferior quality."));

    set_default_weapon(14, 17, W_SWORD, W_SLASH, W_ANYH, 0);
    
    add_prop(OBJ_I_VOLUME, 500);  
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(14,17)+random(100)-50);
}
