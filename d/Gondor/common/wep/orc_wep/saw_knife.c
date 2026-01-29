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
    set_name("knife");
    set_pname("knives");
    set_adj("saw-edged");
    add_adj(({ "black", "long", "orc", "saw edged", "jagged" }));
    set_short("saw-edged knife"); 
    set_long(BSN("A black knife with a long jagged blade. There is some "+
    "dry blood on the blade."));

    set_default_weapon(10, 11, W_KNIFE, W_SLASH, W_ANYH, 0);
    
    add_prop(OBJ_I_VOLUME, 200);  
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(10,11)+random(20)-10);
}
