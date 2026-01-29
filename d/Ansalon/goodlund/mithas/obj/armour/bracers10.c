/* Piece of standard arena equipment */

inherit "/std/armour";

#include <stdproperties.h>
#include <wa_types.h>

void
create_armour()
{
    set_name("bracers");
    set_adj("leather");
    set_short("pair of leather bracers");
    set_pshort("pairs of leather bracers");
    set_long("This is a pair of standard arena bracers. They appear " + 
        "to be light and slightly protective.\n");
    set_ac(10);
    set_at(A_ARMS);
    add_prop(OBJ_I_VOLUME, 300);
}

