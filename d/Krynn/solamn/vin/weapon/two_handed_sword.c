/* created by Aridor 09/15/94 */
/*
 * Added support for the commerce module in July 2002, by Boron
 */

inherit "/std/weapon";
inherit "/d/Genesis/lib/commodity";

#include "../local.h"
#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>

public void
create_weapon()
{
    set_name("longsword");
    set_pname("longswords");
    set_adj("solamnic");
    add_adj("metal");  /* added by Gorboth, July 2007 */

    add_adj("two-handed");
    add_name(({"sword","weapon"}));
    add_pname(({"swords","weapons"}));
    set_short("solamnic two-handed longsword");
    set_pshort("solamnic two-handed longswords");
    set_long("This is the pride of a Solamnic Knight. It is a weapon of " +
         "excellent quality. It is polished to shine so brightly " +
         "that it almost hurts your eyes.\n");

    set_commodity_name ("Sol.2H.lsword"); // required to link this
                                  // object with the domain server
    set_commodity_value(F_VALUE_WEAPON(36,36), 0);


    set_hit(36);
    set_pen(36);
    set_wt(W_SWORD);
    set_dt(W_IMPALE | W_SLASH);
    set_hands(W_BOTH);

    add_prop(OBJ_I_WEIGHT, 3000);
    add_prop(OBJ_I_VOLUME, 6000);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(36,36));
    add_prop(VK_NOBUY, 1);

}

