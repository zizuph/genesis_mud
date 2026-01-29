/*  
 * File: dwarven_chain.c
 * Kragh's warhammer.
 *
 * Blizzard, 05/2003
 */
 
inherit "std/armour.c";
inherit "/lib/keep";

#include <wa_types.h>
#include <macros.h>
#include <formulas.h>
#include "/d/Krynn/common/defs.h"

void
create_armour()
{
    set_name("chainmail");
    set_pname("chainmails");
    add_name(({ "mail", "chain", "armour" }));
    add_pname(({ "mails", "chains", "armours" }));
    set_short("dwarven chain mail");
    set_pshort("dwarven chain mails");
    add_adj(({ "chain", "heavy", "dwarven" }));
    set_ac(33);
    set_am( ({-3,3,0}) );
    set_at(A_BODY | A_ARMS);
    set_long("This heavy suit of chainmail is a product of the masterful " +
        "skill of the dwarves. Made of two thin layers of tiny, but " +
        "unbelievably strong rings, it provides a level of protection " +
        "seldom seen in light armours.\n");
    add_prop(OBJ_I_WEIGHT, 15000);
    add_prop(OBJ_I_VOLUME, 11000);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(33) + random(400));
}
