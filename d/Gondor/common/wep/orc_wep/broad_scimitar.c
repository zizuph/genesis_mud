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
    set_pname("scimitars");
    add_name("swords");
    add_name(({"sword"}));
    set_adj("broad");
    add_adj(({ "orc", "heavy" }));
    set_short("broad scimitar");
    set_pshort("broad scimitars");
    set_long(BSN("A heavy scimitar with a broad curved blade. The scimitar "+
    "is so large that it is almost two-handed."));

    set_default_weapon(29, 25, W_SWORD, W_SLASH, W_ANYH, 0);
    
    add_prop(OBJ_I_VOLUME, 1100);  
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(29,25)+random(200)-100);
}
