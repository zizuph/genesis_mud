/* Piece of standard Mithas arena equipment */

inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>

void
create_armour()
{
    set_name("cap");
    set_adj("leather");
    set_long("This is a standard arena cap. It appears to be very " + 
        "light and slightly protective.\n");
    set_ac(10);
    set_at(A_HEAD);
    add_prop(OBJ_I_VOLUME, 150);
}

