/* The armour of the Vingaard Keep guards.
 * by Teth, Dec. 2 1996
 */
 /*
  * Added support for the commerce module in July 2002, by Boron
  */

inherit "/std/armour";
inherit "/d/Genesis/lib/commodity";

#include <wa_types.h>
#include <formulas.h>
#include "../../local.h"

public void
create_armour()
{
    set_name("chainmail");
    add_name(({"mail","chain","armour"}));
    set_pname("chainmails");
    add_pname(({"mails","chains","armours"}));
    set_adj("solamnic");
    add_adj(({"tempered","steel","chain"}));
    set_short("solamnic chainmail");
    set_pshort("solamnic chainmails");
    set_long("This armour is forged of high quality Solamnic " +
        "steel. It is the standard issue of the Vingaard Keep " +
        "armoury, and is worn as a measure to protect the body.\n");
    set_ac(27);
    set_am( ({-2,3,-1}) );
    set_at(A_BODY);


    set_commodity_name ("s_armour"); // required to link this
                                  // object with the domain server
    set_commodity_value(F_VALUE_ARMOUR(27), 0);

    add_prop(OBJ_I_VOLUME, 3100);
    add_prop(OBJ_I_WEIGHT, 6750);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(27));
    add_prop(VK_NOBUY, 1);
}

