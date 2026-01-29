/* Piece of standard Mithas arena equipment */

inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>

void
create_armour()
{
    set_name("gloves");
    set_adj("leather");
    set_short("pair of leather gloves");
    set_pshort("pairs of leather gloves");
    set_long("This is a pair of standard arena gloves. They appear to fit " + 
        "well and protect the skin of your hands.\n");
    set_ac(5);
    set_at(A_HANDS);
    add_prop(OBJ_I_VOLUME, 150);
}

