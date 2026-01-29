#pragma strict_types

inherit "/std/armour";
inherit "/lib/keep";

#include <stdproperties.h>
#include <wa_types.h>

#define COLOURS ({"red", "green", "purple", "black", "yellow", \
})

public void
create_armour()
{
    string colour = COLOURS[random(sizeof(COLOURS))];

    set_pname(colour + " silk sashes");
    set_pshort(colour + " silk sashes");
    set_short(colour + " silk sash");
    set_name("sash");
    set_adj(colour);
    set_long("A "+ colour + " silk sash that is worn "+
        "about the waist.\n");
    set_at(A_WAIST);
    set_ac(5);
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_VALUE, 500);
}
