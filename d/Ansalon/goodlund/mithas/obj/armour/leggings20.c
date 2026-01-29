/* Piece of standard Mithas arena equipment */

inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>

void
create_armour()
{
    set_name("greaves");
    set_adj("bronze");
    set_short("pair of bronze greaves");
    set_pshort("pairs of bronze greaves");
    set_long("This is a standard pair of arena greaves. They appear to " + 
        "be fairly light and somewhat protective.\n");
    set_ac(20);
    set_at(A_LEGS);
    add_prop(OBJ_I_VOLUME, 1900);
}

