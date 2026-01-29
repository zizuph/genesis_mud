/* Piece of standard Mithas arena equipment */

inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>

void
create_armour()
{
    set_name("leggings");
    set_adj("leather");
    set_short("pair of leather leggings");
    set_pshort("pairs of leather leggings");
    set_long("This is a standard pair of arena leggings. They appear to " + 
        "be very light and slightly protective.\n");
    set_ac(10);
    set_at(A_LEGS);
    add_prop(OBJ_I_VOLUME, 1500);
}

