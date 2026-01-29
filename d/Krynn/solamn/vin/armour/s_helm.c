/* The helmet used by the guards in Vingaard Keep
 * by Teth, December 2, 1996
 */
/*
 * Added support for the commerce module in July 2002, by Boron
 */
inherit "/std/armour";
inherit "/d/Genesis/lib/commodity";

#include <wa_types.h>
#include <formulas.h>

#include "../local.h"

public void
create_armour()
{
    set_name("helm");
    add_name(({"helmet","armour"}));
    set_pname("helms");
    add_pname(({"armours","helmets"}));
    set_adj("solamnic");
    add_adj(({"steel","tempered"}));
    set_short("solamnic helm");
    set_pshort("solamnic helms");
    set_ac(15);
    set_at(A_HEAD);
    set_am( ({-2,3,-1}) );
    set_long("This helmet is made of tempered Solamnian steel. " +
        "Etched into the helm are the words, 'Vingaard Keep " +
        "Armoury Standard Issue'.\n");


    set_commodity_name ("s_helm"); // required to link this
                                  // object with the domain server
    set_commodity_value(F_VALUE_ARMOUR(15), 0);

    add_prop(OBJ_I_VOLUME, 1500);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(15, A_HEAD));
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(15));
    add_prop(VK_NOBUY, 1);
}
