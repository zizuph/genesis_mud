
#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>
inherit "/std/armour";


create_armour()
{
    set_name("shirt");
    set_adj("blue");
    set_long("A bright blue shir.  It is small in size and would "+
      "fit a kender well.\n");
    set_ac(4);
    set_at(A_BODY);
    set_am(({-1,0,0}));
    add_prop(OBJ_I_WEIGHT,300);
    add_prop(OBJ_I_VOLUME,250);
    add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(4));
}
