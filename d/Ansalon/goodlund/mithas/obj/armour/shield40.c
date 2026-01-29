/* Piece of standard Mithas arena equipment */

inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>

void
create_armour()
{
    set_name("shield");
    set_adj("steel");
    set_long("This is a standard arena shield. It appears to be fairly " + 
        "weighty, but extremely protective.\n");
    set_ac(40);
    set_at(A_SHIELD);
    add_prop(OBJ_I_VOLUME, 5500);
}

