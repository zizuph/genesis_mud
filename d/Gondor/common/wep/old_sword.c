/* Weapon coded by Arren, July 94 */ 

inherit "/std/weapon";

#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/formulas.h"
#include "/d/Gondor/defs.h"

void
create_weapon()
{
    set_name("sword");
    set_pname("swords");
    set_adj("old");
    add_adj("hand-and-half");
    set_short("old hand-and-half sword"); 
    set_long(BSN(
        "An old hand-and-half sword which is slightly curved to improve "+
        "slashing attacks. The damasked blade has a pattern of writhing "+
        "snakes in red and gold. The hilt is metal-wired. "));

    set_default_weapon(28, 31, W_SWORD, W_SLASH, W_BOTH, 0);
    
    add_prop(OBJ_I_VOLUME, 1000);  
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(28,31) - random(100));
}
