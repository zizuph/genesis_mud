/* Piece of standard Mithas arena equipment */

inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>

void
create_armour()
{
    set_name("boots");
    set_adj("leather");
    set_short("pair of leather boots");
    set_pshort("pairs of leather boots");
    set_long("This is a pair of standard arena boots. They appear to fit " + 
        "well and protect your feet.\n");
    set_ac(10);
    set_at(A_FEET);
    add_prop(OBJ_I_VOLUME, 250);
}

