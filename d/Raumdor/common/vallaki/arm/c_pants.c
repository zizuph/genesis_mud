inherit "/std/armour";
#include "/d/Raumdor/defs.h"

void
create_armour()
{
    ::create_armour();
    set_name("pants");
    set_adj("leather");
    set_short("leather pants");
    set_long("These are a nice pair of leather pants.\n");
    set_at(A_LEGS);
    set_ac(1);
    add_prop(OBJ_I_WEIGHT,1000);
    add_prop(OBJ_I_VOLUME,800);
    add_prop(OBJ_I_VALUE,100);
}

