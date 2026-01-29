/* Piece of standard arena equipment */

inherit "/std/armour";

#include <stdproperties.h>
#include <wa_types.h>

void
create_armour()
{
    set_name("bracers");
    set_adj("steel");
    set_short("pair of steel bracers");
    set_pshort("pairs of steel bracers");
    set_long("This is a pair of standard arena bracers. They appear " + 
        "to be weighty, but extremely protective.\n");
    set_ac(40);
    set_at(A_ARMS);
    add_prop(OBJ_I_VOLUME, 900);
}

