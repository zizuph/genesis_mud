/* Piece of standard arena equipment */

inherit "/std/armour";

#include <stdproperties.h>
#include <wa_types.h>

void
create_armour()
{
    set_name("bracers");
    set_adj("iron");
    set_short("pair of iron bracers");
    set_pshort("pairs of iron bracers");
    set_long("This is a pair of standard arena bracers. They appear " + 
        "to be very protective, but somewhat weighty.\n");
    set_ac(30);
    set_at(A_ARMS);
    add_prop(OBJ_I_VOLUME, 700);
}

