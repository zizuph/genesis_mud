inherit "/std/armour";
#include "/d/Raumdor/defs.h"

void
create_armour()
{
    ::create_armour();
    set_name("pair of sandals");
    set_pname("pair of sandals");
    add_name("sandal");
    add_name("sandals");
    set_adj("leather");
    set_short("pair of leather sandals");
    set_pshort("pair of leather sandals");
    set_long("These are a nice pair of leather sandals.\n");
    set_at(A_FEET);
    set_ac(1);
    add_prop(OBJ_I_WEIGHT,500);
    add_prop(OBJ_I_VOLUME,300);
    add_prop(OBJ_I_VALUE,30+random(5));
}

