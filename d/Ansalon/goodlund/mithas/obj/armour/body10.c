/* Piece of standard Mithas arena equipment */

inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>

void
create_armour()
{
    set_name("vest");
    set_adj("leather");
    set_long("This is a standard arena vest. It appears to be very " + 
        "light and slightly protective.\n");
    set_ac(10);
    set_at(A_BODY);
    add_prop(OBJ_I_VOLUME, 2500);
}

