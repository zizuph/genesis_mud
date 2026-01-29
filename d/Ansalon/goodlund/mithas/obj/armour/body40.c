/* Piece of standard Mithas arena equipment */

inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>

void
create_armour()
{
    set_name("platemail");
    set_adj("steel");
    set_long("This is a standard arena platemail. It appears to be fairly " + 
        "weighty, but extremely protective.\n");
    set_ac(40);
    set_at(A_BODY);
    add_prop(OBJ_I_VOLUME, 13000);
}

