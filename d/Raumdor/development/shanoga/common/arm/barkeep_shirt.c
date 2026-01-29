#include "defs.h"

inherit "/d/Raumdor/std/armour";

#define SHIRT_COLOURS ({ \
    "dull amber", \
    "dull crimson", \
    "faint scarlet", \
    "crystal blue", \
    "pale green", \
})

void
create_armour()
{
    string colour;
    colour = one_of_list(SHIRT_COLOURS);
    ::create_armour();
    set_name("shirt");
    set_adj(colour);
    set_short(colour + " shirt");
    set_long(".\n");
    set_ac(5);
    set_at(A_TORSO | A_ARMS);
    add_prop(OBJ_I_WEIGHT,300);
    add_prop(OBJ_I_VOLUME,270);
    add_prop(OBJ_I_VALUE,10);
}

