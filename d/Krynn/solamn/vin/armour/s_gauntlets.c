/* The shield used by the guards in Vingaard Keep
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
set_name("gauntlets");
    set_pname("pairs");
    add_name(({"pair", "armour"}));
    add_pname("armours");
    set_adj("solamnic");
    add_adj(({"chain","steel"}));
    set_short("pair of solamnic gauntlets");
    set_pshort("pairs of solamnic gauntlets");
    set_ac(5);
    set_at(A_HANDS);
    set_am( ({0,0,0}) );
set_long("A pair of fine Solamnic gauntlets, stamped with the inscription "+
   "'Vingaard Keep Armoury Standard Issue'.\n");

    set_commodity_name ("s_gauntlets"); // required to link this
                                  // object with the domain server
    set_commodity_value(F_VALUE_ARMOUR(5), 0);

    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(10));
    add_prop(VK_NOBUY, 1);
}
