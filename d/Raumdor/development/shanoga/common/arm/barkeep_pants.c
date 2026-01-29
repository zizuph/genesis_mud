#include "defs.h"

inherit "/d/Raumdor/std/armour";

#define PANTS_COLOURS ({ \
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
    colour = one_of_list(PANTS_COLOURS);
    ::create_armour();
    set_name("pair of pants", 1);
    set_adj(colour);
    set_short(colour + " pair of pants");
    set_pshort(colour + " pairs of pants");
    set_long(".\n");
    set_ac(5);
    set_at(A_LEGS);
    add_prop(OBJ_I_WEIGHT,300);
    add_prop(OBJ_I_VOLUME,270);
    add_prop(OBJ_I_VALUE,10);
}