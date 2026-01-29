/* This is a test armour, perhaps appropriate for my gnomes */

inherit "/std/armour";

#include <wa_types.h>       
#include <formulas.h>      
#include <stdproperties.h>  
#include <macros.h>

#define ARMOUR_CLASS 10

void
    create_armour()
    {
        set_name("trousers");
        set_pname("trousers");

        set_adj("grey");
        set_adj("leather");

        set_short("grey leather trousers");
        set_pshort("leather trousers");

        set_long("These trousers are light, and fairly snug." +
                 " You can imagine stalking through the underbrush" +
                 " in them.\n");

        set_ac(ARMOUR_CLASS);
        set_at(A_LEGS);
        set_am(({ 0,2,-2 }));

        add_prop(OBJ_I_WEIGHT, 2000);
        add_prop(OBJ_I_VOLUME, 1000);
        add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(ARMOUR_CLASS));

    }
