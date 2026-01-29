/* Elven chain mail by Teth, April 5, 1996 */

inherit "/std/armour";
#include "/d/Krynn/common/defs.h"
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

public void
create_armour()
{
    set_name("chainmail");
    set_pname("chainmails");
    add_name(({"chain","mail","armour"}));
    add_pname(({"chains","mails","armours"}));
    set_ac(15); /* Lowered from armour_guide. We don't want it too good. */
    set_am( ({ -2, 3, -1 }) );
    set_at(A_BODY);
    add_adj( ({ "elven", "shining", "mithril" }) );
    set_short("shining elven chainmail");
    set_pshort("shining elven chainmails");
    set_long("This fine set of armour appears to be have once belonged to "+
             "an elven nobleperson. It is constructed of high-quality "+
             "metal, and, like most things of elven make, is lightweight "+
             "and of little burden. The interlocking links of the chainmail "+
             "remain unrusted after many years.\n");
    add_prop(OBJ_I_VOLUME, 2000); /* Reduced due lightness of armour */
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(15, A_BODY));
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(15));
}

