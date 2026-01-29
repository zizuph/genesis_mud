/* Piece of standard Mithas arena equipment */

inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>

void
create_armour()
{
    set_name("greaves");
    set_adj("steel");
    set_short("pair of steel greaves");
    set_pshort("pairs of steel greaves");
    set_long("This is a standard pair of arena greaves. They appear to " + 
        "be weighty and extremely protective.\n");
    set_ac(40);
    set_at(A_LEGS);
    add_prop(OBJ_I_VOLUME, 2700);
}

