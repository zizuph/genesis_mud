#include "defs.h"

inherit "/d/Raumdor/std/armour";

#define APRON_COLOURS ({ \
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
    colour = one_of_list(APRON_COLOURS);
    ::create_armour();
    set_name("apron");
    set_adj(colour);
    set_short(colour + " apron");
    set_long(".\n");
    set_ac(5);
    set_at(A_CHEST | A_WAIST | A_LEGS);
    add_prop(OBJ_I_WEIGHT,300);
    add_prop(OBJ_I_VOLUME,270);
    add_prop(OBJ_I_VALUE,10);
}

