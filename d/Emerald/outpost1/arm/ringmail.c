inherit "std/armour.c";

#include <wa_types.h>
#include <stdproperties.h>

void
create_armour()
{
    set_name("coat");
    set_short("polished ringmail coat");
    add_adj(({"polished", "ringmail"}));
    set_ac(28);
    set_am( ({-3,4,-1}) );
    set_at(A_TORSO);
    set_at(A_LEGS);
    set_at(A_ARMS);
    set_long("This coat of padded ringmail covers the entire body. It has long sleeves " +
        "and nearly goes down to ankle length. It is belted at the waist for a better fit.\n");
    add_prop(OBJ_I_WEIGHT, 2300); 
    add_prop(OBJ_I_VOLUME,  1050);
}
