inherit "/std/armour";
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>

void create_armour()
{
    set_name("tunic");
    set_short("leather tunic");
    add_adj("leather");
    set_long("An old and well used leather tunic. It is of poor quality " + 
            "and it propably won't protect you very well.\n");
   
    set_ac(5 + random(6));
    set_at(A_BODY);
    /* IMPALE, SLASH, BLUDGEON */
    set_am(({2,0,2}));
    set_af(0);
    add_prop(OBJ_I_WEIGHT, 3000);
    add_prop(OBJ_I_VOLUME, 1380);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(20) +random (200) - 100);
}

