/* Piece of standard Mithas arena equipment */

inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>

void
create_armour()
{
    set_name("cloak");
    set_adj("leather");
    set_long("This is a standard arena cloak. It appears to fit " + 
        "well and protect your body in general.\n");
    set_ac(10);
    set_at(A_ROBE);
    add_prop(OBJ_I_VOLUME, 250);
}

