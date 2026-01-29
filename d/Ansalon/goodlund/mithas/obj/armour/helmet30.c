/* Piece of standard Mithas arena equipment */

inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>

void
create_armour()
{
    set_name("helmet");
    set_adj("iron");
    set_long("This is a standard arena helmet. It appears to be slightly " + 
        "weighty and very protective.\n");
    set_ac(30);
    set_at(A_HEAD);
    add_prop(OBJ_I_VOLUME, 350);
}

