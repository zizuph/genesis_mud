/* Piece of standard Mithas arena equipment */

inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>

void
create_armour()
{
    set_name("chainmail");
    set_adj("iron");
    set_long("This is a standard arena chainmail. It appears to be slightly " + 
        "weighty and very protective.\n");
    set_ac(30);
    set_at(A_BODY);
    add_prop(OBJ_I_VOLUME, 7500);
}

