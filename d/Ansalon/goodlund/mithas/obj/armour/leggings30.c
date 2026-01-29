/* Piece of standard Mithas arena equipment */

inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>

void
create_armour()
{
    set_name("greaves");
    set_adj("iron");
    set_short("pair of iron greaves");
    set_pshort("pairs of iron greaves");
    set_long("This is a standard pair of arena greaves. They appear to " + 
        "be slightly weighty and very protective.\n");
    set_ac(30);
    set_at(A_LEGS);
    add_prop(OBJ_I_VOLUME, 2300);
}

