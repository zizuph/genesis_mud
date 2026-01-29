/* Piece of standard arena equipment */

inherit "/std/armour";

#include <stdproperties.h>
#include <wa_types.h>

void
create_armour()
{
    set_name("bracers");
    set_adj("bronze");
    set_short("pair of bronze bracers");
    set_pshort("pairs of bronze bracers");
    set_long("This is a pair of standard arena bracers. They appear " + 
        "to be somewhat protective.\n");
    set_ac(20);
    set_at(A_ARMS);
    add_prop(OBJ_I_VOLUME, 500);
}

